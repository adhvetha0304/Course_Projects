# Tic-Tac Solver (Project 7)

**Course:** CS 211 – Programming Practicum  
**Semester:** Fall 2024  
**Language:** C++

---

## Overview
This project plays perfect Tic-Tac-Toe on an *N × N* grid using a minimax search (alpha–beta pruning for larger boards).  
Headers separate cell logic, board state, and helper utilities; `main.cpp` drives the command-line game.

---

## Files
| File | Description |
| ---- | ----------- |
| `boardcell.h`   | Defines a single cell’s state and coordinates |
| `gameboard.h`   | Board class: move generation, win detection |
| `grid.h`        | Reusable grid utilities |
| `main.cpp`      | Command-line driver: reads board size, lets you play vs. the solver |
| `Makefile`      | Build / run / Valgrind targets |

---

## Build & Run
```bash
make            # builds ./tic_tac
./tic_tac       # play against the solver
```

### Memory-check
```bash
make valgrind
```

---

