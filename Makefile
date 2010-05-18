CXX	:= g++
CXXFLAGS := -g
OBJECTS := 

binpacking2D: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS)

clean:
	rm -rf *.o *.out semantic.cache *.gch *~ *.tex.backup