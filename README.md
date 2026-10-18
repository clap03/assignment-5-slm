Small Language Model (SLM)

Description

This project implements a simple character-based language model in C++17.

The program reads a training text, counts overlapping k-grams and their character transitions, and generates random text using the observed frequencies.

An optional smoothing parameter (alpha) allows the generation of transitions that were not observed in the training text.

Compilation

Compile the program using:

make

To remove the executable and object files:

make clean

Usage

Without smoothing:

./slm k filename length

With smoothing:

./slm -a alpha k filename length

Parameters:

k: positive integer specifying the k-gram length.
filename: path to the training text file.
length: requested total output length, including the initial k-gram.
alpha: optional non-negative smoothing parameter (default: 0).

Examples

./slm 2 input.txt 10
./slm -a 1.0 2 input.txt 10

Implementation

The program is organized into two main classes:

LanguageModel: stores k-gram frequencies, character transition counts, and the training alphabet.

TextGenerator: randomly selects the initial k-gram and generates subsequent characters using weighted sampling.

When alpha is zero, generation may stop early if no outgoing transition is available.

Error Handling

The program reports invalid arguments, missing input files, and training texts that are too short. Errors are printed to standard error with the prefix "slm:".