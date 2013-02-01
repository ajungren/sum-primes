CXX ?= c++
CXXFLAGS ?= -O3 -std=c++0x -pipe

.PHONY: all
all : sum-primes
sum-primes : sum-primes.cc
	$(CXX) $(CXXFLAGS) -o sum-primes sum-primes.cc

