CXXFLAGS= -g -Wall -Wextra -O2

all: create_story

create_story: PROJ-1.cpp PROJ-1.hpp
	g++ -std=c++11 -o create_story PROJ-1.cpp


clean: 
	rm -f format/*.o *.o create_story *~ 

