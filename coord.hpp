#ifndef Coord_hpp
#define Coord_hpp
#include <iostream>

using namespace std;

const int tailleGrille = 20;

class Coord {
	public:
	Coord(int lig, int col);
	int getLig() const;
	int getCol() const;
	friend ostream& operator<<(ostream& out, Coord c);
	bool operator==(Coord a) const;

	private:
	int lig, col;
	
};

enum Direction{N, NE , E , SE, S, SO, O , NO};
 
ostream& operator<<(ostream& out, Direction a);

Direction aDroite(Direction dir);
Direction aGauche(Direction dir);
Direction opposer(Direction dir);

Coord devantCoord(Coord c, Direction d);

Direction generateRandomDirection();
#endif
