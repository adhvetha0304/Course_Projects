# Shortest Word Ladder

**Course:** CS 211 – Programming Practicum  
**Semester:** Fall 2024  
**Language:** C  

---

## Overview
I implemented a **Shortest Word Ladder** solver that finds the minimal sequence of valid dictionary words connecting two given words, changing one letter at a time. It guarantees the shortest ladder by performing a breadth-first search (BFS) over the word graph.

---

## Features
- Loads a filtered dictionary containing only words of the required length  
- BFS guarantees the shortest path  
- Frees all dynamic memory  
- `_quiet_` (`-q`) and `_fast_` (`-f`) command-line flags  
- Valgrind target for leak checking  
- Unit-style test executable (`test.exe`)  
- **Makefile** for build / run / test / Valgrind

---

## Files
| File | Purpose |
| ---- | ------- |
| `main.c` | Core implementation and helper tests |
| `Makefile` | Build + run targets (`make run`, `make valgrind`, …) |
| `Observations.pdf` | My written analysis and discussion of results |

---

## Build & Run

### Build the application
```bash
make build
```

### Run
```bash
make run             # interactive
make run_quiet       # minimal output
make run_fast        # skips slower validation
make run_fast_quiet
```

### Tests
```bash
make build_test
make run_test
```

### Memory-leak check
```bash
make valgrind
```
---

## Core Concepts Used
- Breadth-first search on word graphs
- Dynamic arrays & manual memory management (malloc, free)
- File I/O with getline
- Command-line argument parsing
- Unit testing in plain C
- Build automation with Makefiles
- Leak detection with Valgrind

---

Notes
I completed this project for CS 211 coursework and verified it with the autograder. Results and observations are documented in Observations.pdf.

---
