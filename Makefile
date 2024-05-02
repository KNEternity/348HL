CXX = g++
CXXFLAGS = -Wall -std=c++11

# Define your executable name
EXECUTABLE = program

all: $(EXECUTABLE)

$(EXECUTABLE): boolean_logic.cpp truth_tables.cpp main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(EXECUTABLE)
