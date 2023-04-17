#include "grille.hpp"
#include "coord.hpp"
#include <iostream>


using namespace std;

const float probaTourner = 0.1;
const int dureeSablier = 6;
const float densiteBrindille=0.05;
const int nbTermites=20;

void randTMouv(Grille &g){
    for (int i = 0; i < nbTermites; i++)
    {
        Coord temp = g.trouveTermite(i);
        Direction t = g.dirTermite(temp);
        int ra = rand()%10 +1;
        if (ra <=probaTourner*10){
            t = aGauche(t);
        }
        try
        {
            Coord nouv = devantCoord(temp,t);
            if(g.estVide(nouv)){
            g.enleveTermite(temp);
            g.poseTermite(nouv,i,t);
        }else{
            g.enleveTermite(temp);
            g.poseTermite(temp,i,generateRandomDirection());
        }
        }
        catch(runtime_error)
        {
            g.enleveTermite(temp);
            g.poseTermite(temp,i,generateRandomDirection());
        }
        
        
    }
}

int main() {
    Grille sim;
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
      int x = rand() % 20;
      int y = rand() % 20; 

     while (!sim.estVide({x, y})) {
        x = rand() % 20;
        y = rand() % 20;
    }
        sim.poseTermite({x,y},i,N);
    }
    cout << sim << endl;

    int nbPasse= 10;


    char user = getchar();
    
    while(user != '.')
    {
        for (int i =0 ; i < nbPasse; i++)
        {
            randTMouv(sim);
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
        cout << "Le nombre d'itérations par passe est " << nbPasse << endl;
    }
    

    return 0;
}
