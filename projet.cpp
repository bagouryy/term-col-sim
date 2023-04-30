#include "grille.hpp"
#include "coord.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

const float probaTourner = 0.1;
const int dureeSablier = 6;
const float densiteBrindille=0.10;
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
                if((term[i].sablier >0 || (term[i].sablier <=0 && !g.contientBrindille(nouv)))){
                    Direction d = generateRandomDirection();
                    g.setTermDir(oldC,d);
                    term[i].dir = d;
                    g.setTermTSP(oldC,true);
                    term[i].tourneSurPlace = true;
                }else if(term[i].sablier <=0 && g.contientBrindille(nouv) && term[i].brindille){
                        if (g.voisinsLibre(oldC) <=1){
                            g.setTermDir(oldC,opposer(term[i].dir));
                            term[i].dir = opposer(term[i].dir);
                            g.deplaceTermite(oldC);
                        }else{
                            g.setTermDir(oldC,aGauche(term[i].dir));
                            term[i].dir = aGauche(term[i].dir);
                            dechargerBrindille(g,term[i]);
                        }
                    
                }else if(term[i].sablier <=0 && g.contientBrindille(nouv) && !term[i].brindille){
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



// void rassemblerBrindille(Grille &g,vector<Term> &termites){
//     for (int i = 0; i < nbTermites; i++)
//     {   
//         Term &term= termites[i];
//         Coord cT = g.trouveTermite(i);
//         Direction dT = g.dirTermite(cT);
//         try{
//         Coord dC = devantCoord(cT,dT);
//         if(g.contientBrindille(dC)){
//             if (term.sablier <= 0)
//             {
//                 if (!term.brindille)
//                 {
//                     chargerBrindille(g,term);
//                     g.enleveBrindille(dC);
//                 }else
//                 {
//                     term.dir = aGauche(term.dir);
//                     g.setTermDir(cT,term.dir);
//                     dechargerBrindille(g,term);
//                 }
                
//             }
            
//         }
//         }catch(runtime_error){};
//     }
    
// }

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

void jeu(vector<Term> termites, Grille sim, int &nbPasse){
    char user = getchar();
    
    while(user != '.')
    {
        cout << "Le nombre d'itérations par passe est " << nbPasse << endl;
        for (int i =0 ; i < nbPasse; i++)
        {   
            // randTMouv(sim,termites);
            rassemblerBrindille(sim,termites);
            // testAlgo(sim,termites);
        }
        // cout << termites << endl;
        cout << sim << endl;
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
    
    // Grille test;
    Grille sim;
    vector<Term> termites;
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
   

    sim = grilleJeu(termites);


    // cout << termites << endl;
    cout << sim << endl;
    // cout << test.voisinsLibre({1,1}) << endl;
    // cout << test.voisinsLibre({1,3}) << endl;
    // cout << test.voisinsLibre({0,3}) << endl;
    jeu(termites,sim,nbPasse);

    return 0;
}
