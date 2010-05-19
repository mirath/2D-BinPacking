CXX	:= g++
CXXFLAGS := -g
OBJECTS := binPacking2D.o FiniteBestStrip.o utils.o

binPacking2D: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o binPacking2D

binPacking2D.o: binPacking2D.cpp
	$(CXX) $(CXXFLAGS) -c binPacking2D.cpp

FiniteBestStrip.o: FiniteBestStrip.cpp
	$(CXX) $(CXXFLAGS) -c FiniteBestStrip.cpp FiniteBestStrip.h 

utils.o: utils.cpp
	$(CXX) $(CXXFLAGS) -c utils.cpp utils.h



clean:
	rm -rf *.o *.out semantic.cache *.gch *~ *.tex.backup