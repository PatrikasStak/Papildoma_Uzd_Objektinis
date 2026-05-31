CXX = g++
CXXFLAGS = -std=c++17 -Wall

program: main.cpp func.cpp func.h lib.h
	$(CXX) $(CXXFLAGS) main.cpp func.cpp -o program

clean:
	rm -f program
