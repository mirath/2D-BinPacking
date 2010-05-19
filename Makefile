CXX	:= g++
CXXFLAGS := -g -std=c++0x
OBJECTS := 

binpacking2D: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS)

HFirstBest: HFirstBest.cpp HFirstBest.h
	$(CXX) -c $(CXXFLAGS) HFirstBest.cpp HFirstBest.h

clean:
	rm -rf *.o *.out semantic.cache *.gch *~ *.tex.backup
