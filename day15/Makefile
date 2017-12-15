CXX=gcc
CXXFLAGS=-g -Wall -pedantic -Ofast
SRCS=$(wildcard *.c)
BINS=$(SRCS:%.c=%)

all:
	@$(foreach SRC, $(SRCS), echo building $(SRC)... && $(CXX) $(CXXFLAGS) -o $(SRC:%.c=%) $(SRC);)

clean:
	rm $(BINS)