CXX ?= c++
CXXFLAGS ?= -O3 -std=c++0x -pipe

.PHONY: all clean
all : sum-primes
clean :
	@rm -f sum-primes
sum-primes : sum-primes.cc
	$(CXX) $(CXXFLAGS) -o sum-primes sum-primes.cc

