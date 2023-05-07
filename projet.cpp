#include "grille.hpp"
#include "coord.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


using namespace std;

const float probaTourner = 0.1;
const int dureeSablier = 6;
const float densiteBrindille=0.1;
const int nbTermites=20;
int nbPasse =1;

void randTMouv(Grille &g, vector<Term> &term){
    for (int i = 0; i < nbTermites; i++)
    {
        Coord oldC = g.trouveTermite(i);
        Direction t = term[i].dir;
        term[i].tourneSurPlace = false;
        if ((rand()%10 +1) <=probaTourner*10){
            t = generateRandomDirection();
        }
        try
        {
            Coord nouv = devantCoord(oldC,t);
            if(g.estVide(nouv)){
                cout << "est vide" << endl;
            g.setTermDir(oldC, t);
            term[i].dir = t;
            g.deplaceTermite(oldC);
            term[i].sablier--;
            g.setTermSablier(oldC,term[i].sablier);
        }else{
            Direction d = generateRandomDirection();
            g.setTermDir(oldC,d);
                cout << "pas vide" << endl;

            term[i].tourneSurPlace = true;
            term[i].dir = d;
        }
        }
        catch(runtime_error)
        {
            Direction d = generateRandomDirection();
            g.setTermDir(oldC,d);
            cout << "catch" << endl;

            term[i].tourneSurPlace = true;
            term[i].dir = d;
        }
        
        
    }
}

void chargerBrindille(Grille &g, Term &term){

    try{
        g.enleveBrindille(devantCoord(g.trouveTermite(term.idT),term.dir));
        term.brindille = true;
        g.setTermBrindille(g.trouveTermite(term.idT), true);
        term.sablier = dureeSablier; 
        g.setTermSablier(g.trouveTermite(term.idT), dureeSablier);
    }catch(runtime_error){};
}

void dechargerBrindille(Grille &g, Term &term){
    try{
    if(term.brindille && term.sablier <=0){
        g.poseBrindille(devantCoord(g.trouveTermite(term.idT),term.dir));
        term.brindille = false;
        g.setTermBrindille(g.trouveTermite(term.idT), false);
        term.sablier = dureeSablier;
        g.setTermSablier(g.trouveTermite(term.idT), dureeSablier);
    }
    }catch(runtime_error){};
}

void rassemblerBrindille(Grille &g, vector<Term> &term){
    for (int i = 0; i < nbTermites; i++)
    {   
        Coord oldC = g.trouveTermite(i);
        Direction t = term[i].dir;
        try{
            Coord nouv = devantCoord(oldC,t);
            if (g.estVide(devantCoord(oldC,t))){
                term[i].tourneSurPlace = false;
                g.setTermTSP(oldC,false);
                if ((rand()%10 +1) <=probaTourner*10){
                    t = generateRandomDirection();
                }
                nouv = devantCoord(oldC,t);
                g.setTermDir(oldC, t);
                term[i].dir = t;
                g.deplaceTermite(oldC);
                term[i].sablier--;
                g.setTermSablier(oldC,term[i].sablier);
            }else{
                if((term[i].sablier >0 || (term[i].sablier <=0 && !g.getBrindille(nouv)))){
                    Direction d = generateRandomDirection();
                    g.setTermDir(oldC,d);
                    term[i].dir = d;
                    g.setTermTSP(oldC,true);
                    term[i].tourneSurPlace = true;
                }else if(term[i].sablier <=0 && g.getBrindille(nouv) && term[i].brindille){
                        if (g.voisinsLibre(oldC) <=1){
                            g.setTermDir(oldC,opposer(term[i].dir));
                            term[i].dir = opposer(term[i].dir);
                            g.deplaceTermite(oldC);
                        }else{
                            g.setTermDir(oldC,aGauche(term[i].dir));
                            term[i].dir = aGauche(term[i].dir);
                            dechargerBrindille(g,term[i]);
                        }
                    
                }else if(term[i].sablier <=0 && g.getBrindille(nouv) && !term[i].brindille){
                   chargerBrindille(g,term[i]);
                }
            }
        }
            catch(runtime_error)
            {
                Direction d = generateRandomDirection();
                g.setTermDir(oldC,d);
                term[i].dir = d;
                g.setTermTSP(oldC,true);
                term[i].tourneSurPlace = true;
            }
        }
        
    }

Grille grilleJeu(vector<Term> &termites){
    Grille sim;
    for (int i = 0; i < tailleGrille; i++)
    {
        for (int j = 0; j < tailleGrille; j++)
        {   
            int r = rand()%100;
            if(r < densiteBrindille*100){
            sim.poseBrindille(Coord(i,j));
            }
        }
        
    }
    for (int i = 0; i < nbTermites; i++)
    {
        Term temp;
        temp.idT = i;
        temp.dir = generateRandomDirection();
        temp.sablier =0;
        int x = rand() % 20;
        int y = rand() % 20; 

     while (!sim.estVide({x, y})) {
        x = rand() % 20;
        y = rand() % 20;
    }   
        termites.push_back(temp);
        sim.poseTermite({x,y},i,temp.dir);
    }
    return sim;
}


void affGraphique(Grille &g){
    sf::RenderWindow window(sf::VideoMode(1400, 1400), "Termite Colony Simulation");
    sf::Texture termiteTexture;

    sf::Texture brindilleTexture;

    if (!termiteTexture.loadFromFile("media/termite.png")) {
        cout << "Failed to load termite texture" << endl;
    }

    if (!brindilleTexture.loadFromFile("media/brindille.png")) {
        cout << "Failed to load brindille texture" << endl;
    }
    
    sf::Sprite termiteSprite(termiteTexture);
	termiteSprite.setScale(sf::Vector2f(30.0 / termiteTexture.getSize().x, 60.0 / termiteTexture.getSize().y));
    sf::Sprite brindilleSprite(brindilleTexture);
	brindilleSprite.setScale(sf::Vector2f(30.0 / brindilleTexture.getSize().x, 30.0 / brindilleTexture.getSize().y));

    while(window.isOpen()){

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color(128, 128, 128, 255)); // 255 is the alpha value

            sf::RectangleShape square(sf::Vector2f(1325.f, 1325.f));
            square.setFillColor(sf::Color::White);
            square.setPosition((window.getSize().x - square.getSize().x) / 2, (window.getSize().y - square.getSize().y) / 2);
            window.draw(square);

            for (int i = 0; i < tailleGrille; i++) {
                for (int j = 0; j < tailleGrille; j++) {
                    if (g.getNumTermite({i,j}) != -1) {
                        termiteSprite.setPosition(j*60 +125, i*60 + 125);
                        switch (g.getDirTermite({i,j}))
                        {
                        case N: break;
                        case NE: termiteSprite.setRotation(45);break;
                        case E: termiteSprite.setRotation(90);break;
                        case SE: termiteSprite.setRotation(135);break;
                        case S: termiteSprite.setRotation(180);break;
                        case SO: termiteSprite.setRotation(225);break;
                        case O: termiteSprite.setRotation(270);break;
                        case NO: termiteSprite.setRotation(315);break;
                        default: break;
                        }
                        window.draw(termiteSprite);
                        termiteSprite.setRotation(0);
                        if(g.termID({i,j}).brindille){
                            brindilleSprite.setPosition(j*60 +125, i*60 +125);
                            window.draw(brindilleSprite);
                        }
                    } else if (g.getBrindille({i,j})) {
                        brindilleSprite.setPosition(j*60 + 125, i*60+ 125);
                        window.draw(brindilleSprite);
                    }
                }
        }

            window.display();
            break;
    }

}

void jeu(vector<Term> termites, Grille sim, int &nbPasse){
        // cout << termites << endl;
    //     cout << "Coordonnees des brindilles: " << endl; 

    //     for (int i = 0; i < 20; i++)
    // {
    //     for (int j = 0; j < 20; j++)
    //     {   
    //         if(sim.contientBrindille({i,j})){
    //             cout << "   {" << i << "," << j << "}" << " , ";
    //         }
    //     }
        
    // }   
    // cout << endl;

    char user = getchar();
    
    while(user != '.')
    {
        cout << "Le nombre d'itérations par passe est " << nbPasse << endl;
        for (int i =0 ; i < nbPasse; i++)
        {   
            // randTMouv(sim,termites);
            rassemblerBrindille(sim,termites);
        }
        cout << sim << endl;
        affGraphique(sim);
        if (user == '*')
        {
            nbPasse *=2;
        }else if (user == '/')
        {
            nbPasse = nbPasse / 2;
            if (nbPasse == 0)
            {
                nbPasse =1;
            }
            
        }else if(user == '1'){
            nbPasse = 1;
        }else if(user == '2'){
            nbPasse = 10;
        }else if(user == '3'){
            nbPasse = 100;
        }else if (user == '4'){
            nbPasse = 1000;
        }
        user = getchar();
    }
}


int main() {
    srand(time(nullptr));  

    {//test
    // Grille test;
    // vector<Term> termites;
    // test.poseBrindille({0,0});
    // test.poseBrindille({0,1});
    // test.poseBrindille({0,2});
    // test.poseBrindille({1,2});
    // test.poseBrindille({2,2});
    // test.poseBrindille({2,1});
    // test.poseBrindille({2,0});
    // test.poseBrindille({1,0});
    // test.poseTermite({1,1},0,N);
    // Term temp;
    // temp.idT = 0;
    // temp.dir = N;
    // temp.sablier =0;
    // temp.brindille = true;
    // test.setTermBrindille({2,1},true);
    // termites.push_back(temp);
    // cout << test << endl;
    // chargerBrindille(test,temp);
    // cout << test << endl;
    // temp.sablier = 0;
    // dechargerBrindille(test,temp);
    // cout << test << endl;
    // cout << test.estVide({0,0}) << endl;
    // cout << test.estVide({1,0}) << endl;
    // cout << test.estVide({1,1}) << endl;
    }
    
    Grille sim;
    vector<Term> termites;

    sim = grilleJeu(termites);


    // cout << termites << endl;
    // cout << test.voisinsLibre({1,1}) << endl;
    // cout << test.voisinsLibre({1,3}) << endl;
    // cout << test.voisinsLibre({0,3}) << endl;
    cout << sim << endl;
    
    jeu(termites,sim,nbPasse);

    return 0;
}
