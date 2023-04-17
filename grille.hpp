#ifndef Grille_hpp
#define Grille_hpp
#include <vector>
#include "coord.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>


using namespace std;

enum EtatTerm {sablier,brindille,tourneSurPlace};

struct Term{
    Direction dir;
    int idT;
    EtatTerm etat;
};

struct Case{
	Term term;
	bool brindille;

	Case(){
		brindille = false;
		term.idT = -1;
	}	
};

class Grille{
private:
    Case grille[tailleGrille][tailleGrille];
public:
    Grille();
	void poseBrindille(Coord c);
	void enleveBrindille(Coord c);
	bool contientBrindille(Coord c) const;
	void poseTermite(Coord c, int idT, Direction dir);
	void enleveTermite(Coord c);
	int numéroTermite(Coord c) const;
	Direction dirTermite(Coord c) const;
	bool estVide(Coord c) const;
    Coord trouveTermite(int idT) const;
    
};

ostream& operator<<(ostream& os, Grille g);
#endif