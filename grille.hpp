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
	int nid;
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
	void setTermNid(Coord c, int n_nid);
	bool getBrindille(Coord c) const;
	int getNumTermite(Coord c) const;
	Direction getDirTermite(Coord c) const;
	int getNidTermite(Coord c) const;
	bool estVide(Coord c) const;
    Coord trouveTermite(int idT) const;
	Term termID(Coord c) const;
	int voisinsLibre(Coord c) const;

};

ostream& operator<<(ostream& os, Grille g);

ostream& operator<<(ostream& os, vector<Term> t);

#endif