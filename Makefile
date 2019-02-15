CXXFLAGS= -g -Wall -Wextra -O2

all: executable

executable: PROJ-1.cpp PROJ-1.hpp
	g++ -std=c++11 -o executable PROJ-1.cpp


clean: 
	rm -f format/*.o *.o executable *~ 

