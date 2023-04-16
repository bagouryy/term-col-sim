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
	b.term = -1;
	grille[c.getLig()][c.getCol()] = b;
}

void Grille::enleveBrindille(Coord c){
	if (!contientBrindille(c)){
		throw runtime_error("Case ne contient pas de brindille");
	}
	Case b;
	b.brindille = false;
	b.term = -1;
	grille[c.getLig()][c.getLig()] = b;
}

bool Grille::contientBrindille(Coord c) const{
	return grille[c.getLig()][c.getCol()].brindille;
}

void Grille::poseTermite(Coord c, int idT){
	if(!estVide(c)){
		throw runtime_error("Case n'est pas vide");
	}
	Case b;
	b.brindille = false;
	b.term = idT;
	grille[c.getLig()][c.getCol()] = b;
}

void Grille::enleveTermite(Coord c){
	if (grille[c.getLig()][c.getCol()].brindille || grille[c.getLig()][c.getCol()].term == -1)
	{
		throw runtime_error("Pas de termite à enlever");
	}
	Case b;
	b.brindille = false;
	b.term = -1;
	grille[c.getLig()][c.getCol()] = b;
}

int Grille::numéroTermite(Coord c) const{
	return grille[c.getLig()][c.getCol()].term;
}

bool Grille::estVide(Coord c) const{
	return !grille[c.getLig()][c.getCol()].brindille && grille[c.getLig()][c.getCol()].term == -1;
}
