{\rtf1\ansi\ansicpg1252\cocoartf2822
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 # Shortest Word Ladder\
\
**Course:** CS 211 \'96 Programming Practicum  \
**Semester:** Fall 2024  \
**Language:** C  \
\
---\
\
## Overview\
This program finds the **shortest word ladder** between two given words, changing one letter at a time.  \
Every intermediate step must be a valid dictionary word, and the algorithm guarantees the minimal ladder length by using **breadth-first search (BFS)**.\
\
---\
\
## Features\
- Loads a filtered dictionary of words of the required length  \
- BFS over the implicit word-graph to guarantee the shortest path  \
- Dynamically manages memory and frees all allocations  \
- Command-line flags for _quiet_ (`-q`) and _fast_ (`-f`) modes  \
- Valgrind target for leak checking  \
- Unit-style test executable (`test.exe`) for key helper functions  \
- **Makefile** for one-command build, run, test, and memory analysis\
\
---\
\
## Files\
| File | Purpose |\
| ---- | ------- |\
| `main.c` | Core implementation & helper tests |\
| `Makefile` | Build + run targets (`make run`, `make valgrind`, etc.) |\
| `Observations.pdf` | written analysis / discussion of results |\
\
---\
\
## Build & Run\
\
### Build the main application\
```bash\
make build        # removes old app.exe and compiles main.c\
```\
\
##Run\
```bash\
make run                # interactive prompts\
make run_quiet      # suppresses extra prints\
make run_fast        # skips slower validation\
make run_fast_quiet\
```\
\
##Tests\
```bash\
make build_test   # builds test.exe\
make run_test     # runs unit tests\
```\
\
##Memory-leak check\
```bash\
make valgrind\
```\
---\
\
##Core Concepts Used\
- Breadth-first search on word graphs\
- Dynamic arrays & manual memory management (malloc, free)\
- File input/output (getline)\
- Command-line argument parsing\
- Unit testing in plain C\
- Build automation with Makefiles\
- Leak detection with Valgrind\
\
---\
\
Notes\
Project completed for CS 211 coursework and verified with the autograder.\
Results and observations are documented in Observations.pdf.\
\
---}