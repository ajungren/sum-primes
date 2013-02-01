/*
 * Copyright 2013 Ayron Jungren
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <climits>      // for ULONG_MAX
#include <cmath>        // for sqrt
#include <cstdlib>      // for malloc and strtoul
#include <iostream>     // for cerr and cout

/* If C++11 is available, we can use cinttypes (inttypes.h in C99) to get
 * uint64_t. Otherwise, we need to fall back to unsigned long long (which is
 * almost always 64 bits but not guaranteed to be) */
#if __cplusplus > 199711L
#include <cinttypes>    // for uint64_t
typedef uint64_t uint64;
#else
typedef unsigned long long uint64;
#endif

bool *sieve(uint64 maximum_number) {
    uint64 i, j;
    /* We pre-calculate the sqrt of maximum_number to prevent it from being
     * called repeatedly (the compiler should optimize it out anyway, but there
     * aren't any guarantees about that) */
    uint64 sqrt_of_max = sqrt(maximum_number);
    bool *primes;

    primes = (bool *) malloc(sizeof(bool) * maximum_number + 1);
    if(primes == NULL) {
        std::cerr << "Could not allocate memory" << std::endl;
        return NULL;
    }

    for(i = 0; i < maximum_number; i++)
        primes[i] = true;

    for(i = 2; i <= sqrt_of_max; i++) {
        if(primes[i]) {
            for(j = i * i; j <= maximum_number; j += i)
                primes[j] = false;
        }
    }

    return primes;
}

int main(int argc, char **argv) {
    bool *primes;
    uint64 i, maximum_number, sum = 0;

    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " MAXIMUM_NUMBER" << std::endl;
        return 1;
    }

    /* Because strtoul is used, the maximum number supported is either:
     *   4,294,967,295 where long is 32 bits
     *   18,446,744,073,709,551,615 where long is 64 bits */
    maximum_number = strtoul(argv[1], NULL, 10);
    // Not only is 0 an invalid number, strtoul returns 0 on error
    if(maximum_number == 0) {
        std::cerr << "Invalid number: " << argv[1] << std::endl;
        return 1;
    }
    // Likewise, strtoul returns ULONG_MAX when the number given is too large
    if(maximum_number == ULONG_MAX) {
        std::cerr << "Number too large (largest supported is " << ULONG_MAX << ")" << std::endl;
        return 1;
    }

    primes = sieve(maximum_number);
    if(primes == NULL)
        return 1;

    for(i = 2; i <= maximum_number; i++) {
        if(primes[i])
            sum += i;
    }

    free(primes);
    std::cout << sum << std::endl;

    return 0;
}

