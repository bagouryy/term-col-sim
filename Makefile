CXX=g++
CXXFLAGS= -Wall -std=c++11
EXEC_FILES=test

all: test

test: test.o coord.o grille.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

test.o: coord.hpp grille.hpp
coord.o: coord.hpp
grille.o: grille.hpp coord.hpp

clean:
	rm -f *.o $(EXEC_FILES)
