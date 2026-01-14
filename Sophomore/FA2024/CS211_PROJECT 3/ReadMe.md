# Bit Big Bug Tug – Word Ladder Builder

**Course:** CS 211 – Programming Practicum  
**Semester:** Fall 2024  
**Language:** C  

## Overview
This program builds a **word ladder** between two words by changing **one letter at a time**.  
Each word entered must have the correct length, exist in a dictionary file, and differ by exactly one character from the previous word.

The program is interactive and continues until the ladder reaches the final word, the user enters `DONE`, or the maximum ladder height is reached.

## Features
- Validates word length, dictionary membership, and one-letter differences
- Dynamically manages memory using `malloc`, `realloc`, and `free`
- Builds and displays word ladders step by step
- Marks changed letters using `^` in the completed ladder output
- Handles invalid input through interactive prompts

## Command-Line Arguments (Optional)
- `-n <wordLen>` : length of each word (2–20)
- `-m <maxHeight>` : maximum ladder height (>1)
- `-d <dictFile>` : dictionary filename
- `-s <startWord>` : starting word
- `-f <finalWord>` : target word

If any parameters are missing or invalid, the program prompts the user interactively.

## Compile and Run
```bash
gcc -Wall -Wextra -std=c11 main.c -o wordladder
./wordladder
