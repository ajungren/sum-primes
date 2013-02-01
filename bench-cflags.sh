#!/bin/sh
# Copyright 2013 Ayron Jungren
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

if [ "x$PROG_NAME" = "x" ]; then
    export PROG_NAME="./sum-primes"
fi

if [ "x$PROG_ARGS" = "x" ]; then
    export PROG_ARGS="50000000"
fi

if [ $# -eq 0 ]; then
    echo "Usage: $0 CFLAGS..."
    echo "Benchmark a program with the given CFLAGS (also used for CXXFLAGS) after rebuilding it with \`make'"
    echo "Set PROG_NAME and PROG_ARGS to change what program and arguments are benchmarked"
    echo "  Current PROG_NAME: $PROG_NAME"
    echo "  Current PROG_ARGS: $PROG_ARGS"
    exit 1
fi

_bench() {
    # Run it once to (hopefully) get it in the cache
    $PROG_NAME $PROG_ARGS >/dev/null 2>/dev/null

    # Show what program and arguments will be used
    echo "Running \`$PROG_NAME $PROG_ARGS' five times..."

    for count in 1 2 3 4 5; do
        `which time` -p -- $PROG_NAME $PROG_ARGS 2>&1 | grep real || exit 1
    done
}

export CFLAGS="$*"
export CXXFLAGS="$*"
make clean && make && _bench

