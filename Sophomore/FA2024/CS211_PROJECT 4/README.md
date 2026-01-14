# Popular Vote Minimizer

**Course:** CS 211 – Programming Practicum  
**Semester:** Fall 2024  
**Language:** C  

---

## Overview
This project implements a **Popular Vote Minimizer**, which computes the minimum number of popular votes required to win a U.S. presidential election using state-level electoral data.

The program evaluates combinations of states to determine the smallest subset whose electoral votes meet or exceed the required threshold while minimizing the total popular vote count.

---

## Features
- Processes state election data from input files  
- Computes the minimum popular vote needed to secure an electoral victory  
- Uses recursive and dynamic programming techniques to explore state combinations  
- Supports fast and quiet execution modes via command-line flags  
- Includes a dedicated test suite and memory-safety checks using Valgrind  
- Built and executed using a custom Makefile  

---

## Files
- `MinPopVote.c` – Core implementation of the vote minimization logic  
- `app.c` – Main driver program  
- `test.c` – Unit tests for validating correctness  
- `Makefile` – Build, test, and debugging automation  
- `Results_Analysis.pdf` – Written analysis of results and observations from running the program  

---

## Build and Run

### Run the program
```bash
make run
```


### Fast and quiet modes
```bash
make run_fast
make run_quiet
make run_fast_quiet
```


### Build and run tests
```bash
make build_test
make run_test
```


### Run memory checks with Valgrind
```bash
make valgrind
```

---

## Core Concepts Used
- Recursive and dynamic programming approaches  
- File input/output in C  
- Algorithmic optimization  
- Command-line argument handling  
- Unit testing in C  
- Memory management and leak detection  
- Build automation with Makefiles  

---

## Notes
This project was completed as part of university coursework and tested using an autograder.

---
