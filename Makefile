CXX	:= g++-4.1
CXXFLAGS := -g #-std=c++0x -O0
OBJECTS := binPacking2D.o FiniteBestStrip.o utils.o HFirstBest.o HBestBest.o LocalSearch.o Heuristics.o

all: binPacking2D

binPacking2D: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o binPacking2D
	rm -rf *.o *.out semantic.cache *.gch *~ *.tex.backup

# test: test.o $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) test.o FiniteBestStrip.o utils.o HFirstBest.o HBestBest.o LocalSearch.o Heuristics.o -o test

binPacking2D.o: binPacking2D.cpp
	$(CXX) $(CXXFLAGS) -c binPacking2D.cpp

HFirstBest.o: HFirstBest.cpp 
	$(CXX) $(CXXFLAGS) -c HFirstBest.cpp 

HBestBest.o: HBestBest.cpp 
	$(CXX) $(CXXFLAGS) -c HBestBest.cpp 

Heuristics.o: Heuristics.cpp 
	$(CXX) $(CXXFLAGS) -c Heuristics.cpp 

LocalSearch.o: LocalSearch.cpp 
	$(CXX) $(CXXFLAGS) -c LocalSearch.cpp 

FiniteBestStrip.o: FiniteBestStrip.cpp
	$(CXX) $(CXXFLAGS) -c FiniteBestStrip.cpp

utils.o: utils.cpp
	$(CXX) $(CXXFLAGS) -c utils.cpp

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -rf binPacking2D *.o *.out semantic.cache *.gch *~ *.tex.backup
