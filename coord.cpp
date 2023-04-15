#include "coord.hpp"
#include <iostream>
#include "doctest.h"

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

TEST_CASE("Getters Coord"){
	Coord a(4,10);
	CHECK(a.getLig() == 4);
	CHECK(a.getCol() == 10);
	CHECK_THROWS(Coord(22,12));
	CHECK_THROWS(Coord(10,-12));
}

bool Coord::operator==(Coord a) const{
	return col == a.col && lig == a.lig;
}

TEST_CASE("Coord Egalité"){
	CHECK(Coord(10,10) == Coord(10,10));
	CHECK(Coord(14,14) == Coord(14,14));
	CHECK_FALSE(Coord(10,12) == Coord(15,10));
	CHECK_FALSE(Coord(10,12) == Coord(12,10));
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

TEST_CASE("Tourner Direction"){
	Direction init = Direction::E;
	CHECK(aGauche(aDroite(init)) == init);
	CHECK(aDroite(aGauche(init)) == init);
	Direction dir1 = init;
	Direction dir2 = init;
	for (int i = 0; i < 8; i++)
	{
		dir1 = aGauche(dir1);
		dir2 = aDroite(dir2);
	}
	CHECK(dir1 == init);
	CHECK(dir2 == init);
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

TEST_CASE("devantCoord") {
    Coord c(5, 5);

    CHECK(devantCoord(c, N) == Coord(4, 5));
    CHECK(devantCoord(c, NE) == Coord(4, 6));
    CHECK(devantCoord(c, E) == Coord(5, 6));
    CHECK(devantCoord(c, SE) == Coord(6, 6));
    CHECK(devantCoord(c, S) == Coord(6, 5));
    CHECK(devantCoord(c, SO) == Coord(6, 4));
    CHECK(devantCoord(c, O) == Coord(5, 4));
    CHECK(devantCoord(c, NO) == Coord(4, 4));
}

TEST_CASE("devantCoord sur un bord") {
    Coord c1(0, 0);
    Coord c2(0, 19);
    Coord c3(19, 19);
    Coord c4(19, 0);

    CHECK_THROWS(devantCoord(c1, N));
    CHECK_THROWS(devantCoord(c2, NE));
    CHECK_THROWS(devantCoord(c3, SE));
    CHECK_THROWS(devantCoord(c4, SO));
}

TEST_CASE("tour systematqiue"){
	Coord currentCoord(10, 10);
	Direction currentDir = N;
	currentCoord = devantCoord(currentCoord, currentDir);
	for (int i = 0; i < 4; i++)
	{
		currentDir = aDroite(currentDir);
	}
	currentCoord = devantCoord(currentCoord, currentDir);
	CHECK(currentCoord == Coord(10,10));
}