CXX=g++
CXXFLAGS = -Wall -std=c++11

all: projet

projet: coord.o grille.o projet.o
	$(CXX) $(CXXFLAGS) -o $@ $^
test: grille.o coord.o test.o
	$(CXX) $(CXXFLAGS) -o $@ $^
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

test.o: grille.hpp coord.hpp
coord.o: coord.hpp
grille.o: grille.hpp coord.hpp
projet.o: grille.hpp coord.hpp

check: test
	./test

clean:
	rm -f projet *.o