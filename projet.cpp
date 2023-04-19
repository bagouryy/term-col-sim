#include "grille.hpp"
#include "coord.hpp"
#include <iostream>


using namespace std;

const float probaTourner = 0.1;
const int dureeSablier = 6;
const float densiteBrindille=0.05;
const int nbTermites=1;

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
            term[i].dir = t;
            g.deplaceTermite(oldC);
            term[i].sablier--;
        }else{
            Direction d = generateRandomDirection();
            g.setTermDir(oldC,d);
            term[i].tourneSurPlace = true;
            term[i].dir = d;
        }
        }
        catch(runtime_error)
        {
            Direction d = generateRandomDirection();
            g.setTermDir(oldC,d);
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
    }catch(runtime_error){};
}
void dechargerBrindille(Grille &g, Term &term){
    try{
    if(term.brindille && term.sablier <=0){
        term.brindille = false;
        g.poseBrindille(devantCoord(g.trouveTermite(term.idT),term.dir));
        g.setTermBrindille(g.trouveTermite(term.idT), false);
        term.sablier = dureeSablier;
    }
    }catch(runtime_error){};
}

void rassemblerBrindille(Grille &g,vector<Term> &termites){
    for (int i = 0; i < nbTermites; i++)
    {   
        Term &term= termites[i];
        Coord cT = g.trouveTermite(i);
        Direction dT = g.dirTermite(cT);
        try{
        Coord dC = devantCoord(cT,dT);
        if(g.contientBrindille(dC)){
            if (term.sablier <= 0)
            {
                if (!term.brindille)
                {
                    chargerBrindille(g,term);
                }else
                {
                    term.dir = aGauche(term.dir);
                    dechargerBrindille(g,term);
                }
                
            }
            
        }
        }catch(runtime_error){};
    }
    
}

int main() {
    /*
    Grille test;
    vector<Term> termites;
    test.poseBrindille({0,0});
    test.poseTermite({1,0},0,N);
    Term temp;
    temp.idT = 0;
    temp.dir = N;
    temp.sablier =0;
    termites.push_back(temp);
    cout << test << endl;
    chargerBrindille(test,temp);
    cout << test << endl;
    temp.sablier = 0;
    dechargerBrindille(test,temp);
    cout << test << endl;

    */
    Grille sim;
    vector<Term> termites;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
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
    cout << sim << endl;


    int nbPasse= 1000;


    char user = getchar();
    
    while(user != '.')
    {
        cout << "Le nombre d'itérations par passe est " << nbPasse << endl;
        for (int i =0 ; i < nbPasse; i++)
        {   
            randTMouv(sim,termites);
            //rassemblerBrindille(sim,termites);
        }
        cout << sim << endl;
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
            
        }
        user = getchar();
    }


    return 0;
}
