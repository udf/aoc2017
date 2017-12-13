CXX=g++
CXXFLAGS=-g -std=c++1z -Wall -pedantic -Ofast
SRCS=$(wildcard *.cpp)
BINS=$(SRCS:%.cpp=%)

all:
	@$(foreach SRC, $(SRCS), echo building $(SRC)... && $(CXX) $(CXXFLAGS) -o $(SRC:%.cpp=%) $(SRC);)

clean:
	rm $(BINS)