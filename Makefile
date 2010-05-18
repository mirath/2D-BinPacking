# Define the symbols we might want to change:
    CXX	:= g++
    CXXFLAGS := -g

    OBJECTS := 
    graph: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS)
