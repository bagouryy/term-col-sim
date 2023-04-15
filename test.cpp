#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "coord.hpp"
#include "grille.hpp"
#include <iostream>

using namespace std;

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
    g.poseTermite({1, 1}, 0);
    CHECK_EQ(g.numéroTermite({1, 1}), 0);
    CHECK_FALSE(g.estVide({1, 1}));
    CHECK_THROWS(g.poseTermite({1, 1}, 1));
}


TEST_CASE("Grille - enleveTermite()") {
    Grille g;
    g.poseTermite({1, 1}, 0);
    g.enleveTermite({1, 1});
    CHECK_EQ(g.numéroTermite({1, 1}), -1);
    CHECK(g.estVide({1, 1}));
    CHECK_THROWS(g.enleveTermite({1, 1}));
}


TEST_CASE("Grille - numéroTermite()") {
    Grille grille;
    CHECK(grille.numéroTermite(Coord(0, 0)) == -1);
    grille.poseTermite(Coord(0, 0), 1);
    CHECK(grille.numéroTermite(Coord(0, 0)) == 1);
    grille.enleveTermite(Coord(0, 0));
    CHECK(grille.numéroTermite(Coord(0, 0)) == -1);
}

TEST_CASE("Grille - estVide()") {
    Grille g;
    CHECK(g.estVide({1, 1}));
    g.poseBrindille({1, 1});
    CHECK_FALSE(g.estVide({1, 1}));
    g.poseTermite({0, 0}, 0);
    CHECK_FALSE(g.estVide({0, 0}));
}

TEST_CASE("Grille output operator") {
    Grille grille;

    // Add some brindilles and termites to the grid
    grille.poseBrindille(Coord(0, 1));
    grille.poseTermite(Coord(1, 1), 0);
    grille.poseBrindille(Coord(2, 1));
    grille.poseTermite(Coord(3, 3), 1);

    // Create a stringstream to capture the output
    stringstream ss;
    ss << grille;

    // Check that the output is correct
    std::string expected_output =
        "  *                                     \n"
        "  T                                     \n"
        "  *                                     \n"
        "      T                                 \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n"
        "                                        \n";
    CHECK(ss.str() == expected_output);
}
