CXX ?= g++
CXXFLAGS ?= -march=native -O3 -pedantic -pipe -std=c++0x -Wall

.PHONY: all clean
all : sum-primes
clean :
	@rm -f sum-primes
sum-primes : sum-primes.cc
	$(CXX) $(CXXFLAGS) -o sum-primes sum-primes.cc

