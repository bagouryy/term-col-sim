#include "coord.hpp"
#include <iostream>


using namespace std;

Coord::Coord(int nlig, int ncol){
	if (nlig < tailleGrille && ncol < tailleGrille && nlig >= 0 && ncol >= 0){
		lig = nlig;
		col = ncol;
	} else {
		throw runtime_error("La taille de la grille est 20, choissisez des nombres entre 0 et 19");
	}
}

int Coord::getCol() const{
	return col;
}

int Coord::getLig() const{
	return lig;
}

ostream& operator<<(ostream& out,Coord c){
	out << "(" << c.getLig() << "," << c.getCol() << ")";
	return out;
}



bool Coord::operator==(Coord a) const{
	return col == a.col && lig == a.lig;
}



ostream& operator<<(ostream& out,Direction a){
	switch(a){
		case N: out << "Nord" << endl;return out;
		case NE: out << "Nord-Est" << endl;return out;
		case E: out << "Est" << endl;return out;
		case SE: out << "Sud-Est" << endl;return out;
		case S: out << "Sud" << endl;return out;
		case SO: out << "Sud-Ouest" << endl;return out;
		case O: out << "Ouest" << endl;return out;
		case NO: out << "Nord-Ouest" << endl;return out;
		default:return out;
	}
}

Direction aDroite(Direction dir) {
    int i = static_cast<int>(dir);
    return static_cast<Direction>((i + 1) % 8);
}
Direction aGauche(Direction dir) {
    switch (dir) {
        case N: return NO;
        case NE: return N;
        case E: return NE;
        case SE: return E;
        case S: return SE;
        case SO: return S;
        case O: return SO;
        case NO: return O;
        default: return N;
    }
}

Direction opposer(Direction dir){
    switch (dir) {
        case N: return S;
        case NE: return SO;
        case E: return O;
        case SE: return NO;
        case S: return N;
        case SO: return NE;
        case O: return E;
        case NO: return SE;
        default: return N;
    }
}


Coord devantCoord(Coord c, Direction d){
	switch (d)
	{
	case N: return Coord(c.getLig()-1,c.getCol());
	case NE: return Coord(c.getLig()-1,c.getCol()+1);
    case E: return Coord(c.getLig(),c.getCol()+1);
    case SE: return Coord(c.getLig()+1,c.getCol()+1);
    case S: return Coord(c.getLig()+1,c.getCol());
    case SO: return Coord(c.getLig()+1,c.getCol()-1);
    case O: return Coord(c.getLig(),c.getCol()-1);
    case NO: return Coord(c.getLig()-1,c.getCol()-1);
	}
}

Direction generateRandomDirection() {
    int randomNum = rand() % 8;
    switch (randomNum) {
        case 0:
            return N;
        case 1:
            return NE;
        case 2:
            return E;
        case 3:
            return SE;
        case 4:
            return S;
        case 5:
            return SO;
        case 6:
            return O;
        case 7:
            return NO;
        default:
            return N;
    }
}
