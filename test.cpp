#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "coord.hpp"
#include "grille.hpp"
#include <iostream>

using namespace std;

TEST_CASE("Getters Coord"){
	Coord a(4,10);
	CHECK(a.getLig() == 4);
	CHECK(a.getCol() == 10);
	CHECK_THROWS(Coord(22,12));
	CHECK_THROWS(Coord(10,-12));
}

TEST_CASE("Coord Egalité"){
	CHECK(Coord(10,10) == Coord(10,10));
	CHECK(Coord(14,14) == Coord(14,14));
	CHECK_FALSE(Coord(10,12) == Coord(15,10));
	CHECK_FALSE(Coord(10,12) == Coord(12,10));
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

TEST_CASE("Test Coord output operator") {
    Coord a(12,10);
    ostringstream os;
    os << a;
    CHECK(os.str() == "(12,10)");
}

TEST_CASE("Grille - poseBrindille()") {
    Grille g;
    g.poseBrindille({1, 1});
    CHECK(g.contientBrindille({1, 1}));
    CHECK_FALSE(g.estVide({1, 1}));
    CHECK_THROWS(g.poseBrindille({1, 1}));
}

TEST_CASE("Grille - enleveBrindille()") {
    Grille g;
    g.poseBrindille({1, 1});
    g.enleveBrindille({1, 1});
    CHECK_FALSE(g.contientBrindille({1, 1}));
    CHECK(g.estVide({1, 1}));
    CHECK_THROWS(g.enleveBrindille({1, 1}));
}


TEST_CASE("Grille - contientBrindille()") {
    Grille grille;
    CHECK_FALSE(grille.contientBrindille(Coord(0, 0)));
    grille.poseBrindille(Coord(0, 0));
    CHECK(grille.contientBrindille(Coord(0, 0)));
    grille.enleveBrindille(Coord(0, 0));
    CHECK_FALSE(grille.contientBrindille(Coord(0, 0)));
}

TEST_CASE("Grille - poseTermite()") {
    Grille g;
    g.poseTermite({1, 1}, 0,N);
    CHECK_EQ(g.numéroTermite({1, 1}), 0);
    CHECK_FALSE(g.estVide({1, 1}));
    CHECK_THROWS(g.poseTermite({1, 1}, 1,N));
}


TEST_CASE("Grille - enleveTermite()") {
    Grille g;
    g.poseTermite({1, 1}, 0,N);
    g.enleveTermite({1, 1});
    CHECK_EQ(g.numéroTermite({1, 1}), -1);
    CHECK(g.estVide({1, 1}));
    CHECK_THROWS(g.enleveTermite({1, 1}));
}


TEST_CASE("Grille - numéroTermite()") {
    Grille grille;
    CHECK(grille.numéroTermite(Coord(0, 0)) == -1);
    grille.poseTermite(Coord(0, 0), 1,N);
    CHECK(grille.numéroTermite(Coord(0, 0)) == 1);
    grille.enleveTermite(Coord(0, 0));
    CHECK(grille.numéroTermite(Coord(0, 0)) == -1);
}

TEST_CASE("Grille - estVide()") {
    Grille g;
    CHECK(g.estVide({1, 1}));
    g.poseBrindille({1, 1});
    CHECK_FALSE(g.estVide({1, 1}));
    g.poseTermite({0, 0}, 0,N);
    CHECK_FALSE(g.estVide({0, 0}));
}

TEST_CASE("Grille output operator") {
    Grille grille;

    // Add some brindilles and termites to the grid
    grille.poseBrindille(Coord(0, 1));
    grille.poseTermite(Coord(1, 1), 0,N);
    grille.poseBrindille(Coord(2, 1));
    grille.poseTermite(Coord(3, 3), 1,N);

    // Create a stringstream to capture the output
    stringstream ss;
    ss << grille;

    // Check that the output is correct
    string expected_output =
"+----------------------------------------+\n"
"|  *                                     |\n"
"|  |                                     |\n"
"|  *                                     |\n"
"|      |                                 |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"|                                        |\n"
"+----------------------------------------+\n";
    CHECK(ss.str() == expected_output);
}
