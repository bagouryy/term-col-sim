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
    int sablier =0;
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
	void poseTermite(Coord c, int idT, Direction dir);
	void enleveTermite(Coord c);
	void deplaceTermite(Coord old);
	void setTermBrindille(Coord c, bool b);
	void setTermDir(Coord c, Direction d);
	void setTermTSP(Coord c, bool TSP);
	void setTermSablier(Coord c, int sablier);
	bool contientBrindille(Coord c) const;
	int numéroTermite(Coord c) const;
	Direction dirTermite(Coord c) const;
	bool estVide(Coord c) const;
    Coord trouveTermite(int idT) const;
	Term termID(Coord c) const;
	int voisinsLibre(Coord c) const;

};

ostream& operator<<(ostream& os, Grille g);

ostream& operator<<(ostream& os, vector<Term> t);

#endif