# [Day 1: "The Tyranny of the Rocket Equation"](https://adventofcode.com/2019/day/1)

## Language

[Pyth](https://esolangs.org/wiki/Pyth) is a Python-based golfing language.

You can most easily run it in an [online interpreter](https://tio.run/#pyth).

## Puzzle A

Just some light number munching.

Pyth is not terribly readable:

````pyth
#=Z+Z-/E3 2)Z
````

[Try it online!](https://tio.run/##K6gsyfj/X9k2SjtKV9/VWMFIM@r/f0MjLkMTLkNLM0suQwMDc1MzAA "Pyth – Try It Online")

The variable `Z` is initialised at 0, so it's helpful for computing the sum.

I loop over the input, with `#` to swallow the EoF error. At each step, I evaluate the input with `E`, get the fuel mass for that value, and add it to the sum.

`)` ends the loop, and I print the total value.

## Puzzle B

Straightforward solution, neither very elegant nor golfed.

````pyth
# aYE;FGY=N0=G-/G3 2W>G0=+NG=G-/G3 2)=+ZN)Z
````

[Try it online!](https://tio.run/##K6gsyfj/X1khMdLV2s090tbPwNZdV9/dWMEo3M7dwFbbzx3G17TVjvLTjPr/39CIy9CEy9DSzJLL0MDA3NQMAA "Pyth – Try It Online")

The first loop reads all the input into a list; the space suppresses printing after each append.

The main body is a nested loop: For each module, add fuel as long as the fuel increments are positive, then add to the total fuel needed.

Note that we're computing the *fuel* mass, not the total mass: don't include the masses of the modules themselves in the sum.
