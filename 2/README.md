# [Day 2: "1202 Program Alarm"](https://adventofcode.com/2019/day/2)

## Language

[C](https://en.wikipedia.org/wiki/C_\(programming_language\)). Specifically C99, with some modern extensions like [`getline`](https://linux.die.net/man/3/getline).

## How to run

Requires [autoreconf](https://linux.die.net/man/1/autoreconf) and [Check](https://libcheck.github.io/check/).

### Build

````bash
autoreconf --install
./configure
make
````

### Tests

````bash
make check
````

### Run

````bash
./src/main target-int
````

with the intcode program as input.

## Puzzle A

The function `program_run_with_alarm` solves puzzle A.

The puzzle itself is trivial, but consuming the input was a real pain. Did you know this

````c
strtok("a,b", ",");
````

is undefined behaviour? To avoid such nasty surprises, make a copy of the string and work with that alone.

## Puzzle B

The goal of puzzle B is to find the pair of inputs that give a specific output. I try brute force first, and it solves the puzzle in 125ms on my machine. Good enough!
