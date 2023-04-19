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
	grille[c.getLig()][c.getCol()] = b;
	cout << "enlever" << endl;
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
	Case old;
	old.brindille = false;
	old.term.idT = -1;
	grille[c.getLig()][c.getCol()] = old;
}

void Grille::deplaceTermite(Coord c){
	if (grille[c.getLig()][c.getCol()].brindille || grille[c.getLig()][c.getCol()].term.idT == -1)
	{
		throw runtime_error("Pas de termite à enlever");
	}
	Case b;
	b.brindille = false;
	Term temp = termID(c);
	b.term = temp;
	if(!estVide({devantCoord(c,temp.dir).getLig(),devantCoord(c,temp.dir).getCol()})){
		throw runtime_error("Case n'est pas vide");
	}

	grille[devantCoord(c,temp.dir).getLig()][devantCoord(c,temp.dir).getCol()] = b;
	Case old;
	old.brindille = false;
	Term oT;
	oT.idT = -1;
	oT.brindille =false;
	old.term = oT;
	grille[c.getLig()][c.getCol()] = old;
}

int Grille::numéroTermite(Coord c) const{
	return grille[c.getLig()][c.getCol()].term.idT;
}

Direction Grille::dirTermite(Coord c) const{
	return grille[c.getLig()][c.getCol()].term.dir;
}

bool Grille::estVide(Coord c) const{
	return !grille[c.getLig()][c.getCol()].brindille && (grille[c.getLig()][c.getCol()].term.idT == -1);
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
	throw runtime_error("Termite not found");
}

Term Grille::termID(Coord c) const{
	return grille[c.getLig()][c.getCol()].term;
}

void Grille::setTermBrindille(Coord c,bool b){
	Term temp = grille[c.getLig()][c.getCol()].term;
	temp.brindille = b;
	grille[c.getLig()][c.getCol()].term = temp;
}

void Grille::setTermDir(Coord c, Direction d){
	Term temp = grille[c.getLig()][c.getCol()].term;
	temp.dir = d;
	grille[c.getLig()][c.getCol()].term = temp;
}

void Grille::setTermSablier(Coord c, int sablier){
	Term temp = grille[c.getLig()][c.getCol()].term;
	temp.sablier = sablier;
	grille[c.getLig()][c.getCol()].term = temp;
}

void Grille::setTermTSP(Coord c, bool TSP){
	Term temp = grille[c.getLig()][c.getCol()].term;
	temp.tourneSurPlace = TSP;
	grille[c.getLig()][c.getCol()].term = temp;
}

ostream& operator<<(ostream& os, Grille g){
    // Print top border
    os << "+" << string(tailleGrille * 2, '-') << "+" << endl;
    
    for (int i = 0; i < tailleGrille; i++) {
        os << "|";
        for (int j = 0; j < tailleGrille; j++) {
            if (g.estVide(Coord(i,j))) {
                os << " ";
            } else if (g.contientBrindille(Coord(i,j))) {
                os << "*";
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
            }
				if (g.termID({i,j}).brindille)
				{
					os << "*";
				}
				else
				{
					os << " ";
				}
				
        }
        os << "|" << endl;
    }

    os << "+" << string(tailleGrille * 2, '-') << "+" << endl;
    
    return os;
}

ostream& operator<<(ostream& os, vector<Term> t){
	os << "Informations Termites: " << endl;
	for (int i = 0; i < t.size(); i++)
	{
		os << "Termite Id : " << i << endl;
		os << "	Termite Direction " << t[i].dir << endl;
		os << "	Termite à brindille? " << t[i].brindille << endl;
		os << "	Termite Sablier : " << t[i].sablier << endl;
		os << "	Termite tourne sur place? " << t[i].tourneSurPlace << endl;	
		}
	return os;
}
