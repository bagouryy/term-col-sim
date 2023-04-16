#include "grille.hpp"
#include "coord.hpp"
#include <iostream>

using namespace std;

int main() {
    Grille g;
    g.poseBrindille(Coord(2,3));
    g.poseBrindille(Coord(3,3));
    g.poseBrindille(Coord(4,3));
    g.poseBrindille(Coord(5,3));
    g.poseBrindille(Coord(6,3));
    g.poseBrindille(Coord(7,3));
    g.poseBrindille(Coord(8,3));
    g.poseBrindille(Coord(9,3));
    g.poseBrindille(Coord(10,3));
    g.poseBrindille(Coord(11,3));
    g.poseBrindille(Coord(12,3));
    g.poseBrindille(Coord(13,3));
    g.poseBrindille(Coord(14,3));
    g.poseBrindille(Coord(15,3));
    g.poseBrindille(Coord(16,3));
    g.poseBrindille(Coord(17,3));
    g.poseBrindille(Coord(18,3));
    g.poseBrindille(Coord(19,3));
    g.poseBrindille(Coord(3,10));
    g.poseBrindille(Coord(4,10));
    g.poseBrindille(Coord(5,10));
    g.poseBrindille(Coord(6,10));
    g.poseBrindille(Coord(7,10));
    g.poseBrindille(Coord(8,10));
    g.poseBrindille(Coord(9,10));
    g.poseBrindille(Coord(10,10));
    g.poseBrindille(Coord(11,10));
    g.poseBrindille(Coord(12,10));
    g.poseBrindille(Coord(13,10));
    g.poseBrindille(Coord(14,10));
    g.poseBrindille(Coord(15,10));
    g.poseBrindille(Coord(16,10));
    g.poseBrindille(Coord(17,10));
    g.poseBrindille(Coord(18,10));
    g.poseBrindille(Coord(5,5));
    g.poseBrindille(Coord(6,5));
    g.poseBrindille(Coord(7,5));
    g.poseBrindille(Coord(8,5));
    g.poseBrindille(Coord(9,5));
    g.poseBrindille(Coord(10,5));
    g.poseTermite(Coord(1,1), 1);
    g.poseTermite(Coord(1,5), 2);
    g.poseTermite(Coord(15,15), 3);
    cout << g << endl;
    return 0;
}