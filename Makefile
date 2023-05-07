CXX=g++
CXXFLAGS = -Wall -std=c++11 -I/usr/local/include
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system

all: projet

projet: coord.o grille.o projet.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test: grille.o coord.o test.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

test.o: grille.hpp coord.hpp
coord.o: coord.hpp
grille.o: grille.hpp coord.hpp
projet.o: grille.hpp coord.hpp

check: test
	./test

clean:
	rm -f projet test *.o
