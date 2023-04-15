#ifndef Grille_hpp
#define Grille_hpp
#include <vector>
#include "coord.hpp"
#include <sstream>
#include <iostream>

using namespace std;

struct Case{
	int term;
	bool brindille;

	Case(){
		brindille = false;
		term = -1;
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
	void poseTermite(Coord c, int idT);
	void enleveTermite(Coord c);
	int numéroTermite(Coord c) const;
	bool estVide(Coord c) const;
};

inline ostream& operator<<(ostream& os, Grille g){
    for (int i = 0; i < tailleGrille; i++) {
        for (int j = 0; j < tailleGrille; j++) {
            if (g.estVide(Coord(i,j))) {
                os << "  ";
            } else if (g.contientBrindille(Coord(i,j))) {
                os << "* ";
            } else {
                os << "T ";
            }
        }
        os << endl;
    }
    return os;
}


#endif