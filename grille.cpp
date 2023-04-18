#include "grille.hpp"

using namespace std;

Grille::Grille(){
	for (int i = 0; i < tailleGrille; ++i) {
        for (int j = 0; j < tailleGrille; ++j) {
            grille[i][j] = Case();
        }
    }
}

void Grille::poseBrindille(Coord c){
	if(!estVide(c)){
		throw runtime_error("Case n'est pas vide");
	}
	Case b;
	b.brindille = true;
	b.term.idT = -1;
	grille[c.getLig()][c.getCol()] = b;
}

void Grille::enleveBrindille(Coord c){
	if (!contientBrindille(c)){
		throw runtime_error("Case ne contient pas de brindille");
	}
	Case b;
	b.brindille = false;
	b.term.idT = -1;
	grille[c.getLig()][c.getLig()] = b;
}

bool Grille::contientBrindille(Coord c) const{
	return grille[c.getLig()][c.getCol()].brindille;
}

void Grille::poseTermite(Coord c, int idT, Direction dir){
	if(!estVide(c)){
		throw runtime_error("Case n'est pas vide");
	}
	Case b;
	b.brindille = false;
	b.term.idT = idT;
	b.term.dir = dir;
	grille[c.getLig()][c.getCol()] = b;
}

void Grille::enleveTermite(Coord c){
	if (grille[c.getLig()][c.getCol()].brindille || grille[c.getLig()][c.getCol()].term.idT == -1)
	{
		throw runtime_error("Pas de termite à enlever");
	}
	Case b;
	b.brindille = false;
	b.term.idT = -1;
	grille[c.getLig()][c.getCol()] = b;
}

int Grille::numéroTermite(Coord c) const{
	return grille[c.getLig()][c.getCol()].term.idT;
}

Direction Grille::dirTermite(Coord c) const{
	return grille[c.getLig()][c.getCol()].term.dir;
}

bool Grille::estVide(Coord c) const{
	return !grille[c.getLig()][c.getCol()].brindille && grille[c.getLig()][c.getCol()].term.idT == -1;
}

Coord Grille::trouveTermite(int idT) const{
	for (int i = 0; i < tailleGrille; i++)
	{
		for (int j = 0; j < tailleGrille; j++)
		{
			if(!estVide({i,j}) && !contientBrindille({i,j})){
				if(idT == numéroTermite({i,j})){
					return {i,j};
				}
			}
		}
		
	}
	throw runtime_error("Not found");
}

bool Grille::termABrindille(int idT) const{
	return grille[trouveTermite(idT).getLig()][trouveTermite(idT).getCol()].term.brindille;
}


ostream& operator<<(ostream& os, Grille g){
    // Print top border
    os << "+" << string(tailleGrille * 2, '-') << "+" << endl;
    
    for (int i = 0; i < tailleGrille; i++) {
        os << "|";
        for (int j = 0; j < tailleGrille; j++) {
            if (g.estVide(Coord(i,j))) {
                os << "  ";
            } else if (g.contientBrindille(Coord(i,j))) {
                os << "* ";
            } else {
				switch (g.dirTermite({i,j}))
				{
				case N:case S: os << "|";
					break;
				case O:case E: os << "-";
					break;
				case NO:case SE: os << "\\";
					break;
				case NE:case SO: os << "/";
					break;
				
				default:
					break;
				}
				if (g.termABrindille(g.numéroTermite({i,j})))
				{
					os << "*";
				}
				else
				{
					os << " ";
				}
				
            }
        }
        os << "|" << endl;
    }

    // Print bottom border
    os << "+" << string(tailleGrille * 2, '-') << "+" << endl;
    
    return os;
}