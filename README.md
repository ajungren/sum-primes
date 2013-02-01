# sum-primes
## Calculate the sum of all primes under a given number

### Building

To build `sum-primes`, just run `make`. If you want to use a different C++
compiler, or set different flags, set either `CXX` or `CXXFLAGS` in your
environment before running `make`. (Check your shell's manual for information.)
`sum-primes` will use C++11 if it is available, but it does not require it.

### Usage

To use `sum-primes`, run `./sum-primes $MAX` replacing `$MAX` with the number
you want `sum-primes` to stop at. `sum-primes` is **not** inclusive, so if you
want the sum of all primes up to and including 923869, run `./sum-primes 923870`.

### Speed

`sum-primes` uses the [sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes),
so it is rather fast. On a Core 2 Quad @ 2.50 GHz box running Gentoo Linux, it
takes 0.048s with no flags given to `g++`, and 0.017s with `-march=native -O3`.
Both times were measured with `time` (real time) and averaged over five runs.
`sum-primes` was built leaning heavily toward speed with respect to speed vs.
memory tradeoffs. It would be possible to use `std::vector<bool>` instead of a
C-style array of `bool`s, but that would make `sum-primes` run slower while
reducing memory usage (`std::vector<bool>` frequently, depending on
implementation, packs multiple `bool`s together into one byte whereas C-style
arrays of `bool`s do not).

