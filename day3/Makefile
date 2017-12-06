CXX=g++
CXXFLAGS=-g -std=c++1z -Wall -pedantic

SRC=$(wildcard *.cpp)
BIN=$(SRC:%.cpp=%)

all: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $^
	./$(BIN)

clean:
	rm $(BIN)