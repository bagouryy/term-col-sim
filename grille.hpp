#ifndef Grille_hpp
#define Grille_hpp
#include <vector>
#include "coord.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>


using namespace std;

struct Term{
    Direction dir;
    int idT;
    int sablier;
	bool brindille = false;
	bool tourneSurPlace;
	Term(){
		idT=-1;
	}
};

struct Case{
	Term term;
	bool brindille;

	Case(){
		brindille = false;
		term.idT = -1;
	};	
};

class Grille{
private:
    Case grille[tailleGrille][tailleGrille];
public:
    Grille();
	void poseBrindille(Coord c);
	void enleveBrindille(Coord c);
	void deplaceTermite(Coord old);
	bool contientBrindille(Coord c) const;
	void poseTermite(Coord c, int idT, Direction dir);
	void enleveTermite(Coord c);
	int numéroTermite(Coord c) const;
	Direction dirTermite(Coord c) const;
	bool estVide(Coord c) const;
    Coord trouveTermite(int idT) const;
	Term termID(Coord c) const;
	void setTermBrindille(Coord c, bool b);
	void setTermDir(Coord c, Direction d);
};

ostream& operator<<(ostream& os, Grille g);
#endif