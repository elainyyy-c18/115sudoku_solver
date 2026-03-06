# Sudoku Solver (C++)

A C++ project that solves Sudoku puzzles using a **backtracking algorithm**.

---

## Project Structure

```
sudoku-solver/
│
├─ src/
│   └─ sudoku.cpp
│
├─ include/
│   └─ sudoku.h
│
├─ main.cpp
├─ README.md
├─ CMakeLists.txt
└─ .gitignore
```

---

## Build

### Using g++

```bash
g++ main.cpp src/sudoku.cpp -o sudoku_solver
./sudoku_solver
```

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
./sudoku_solver
```

---

## Algorithm

This project solves Sudoku using a **backtracking search algorithm**.

The algorithm works as follows:

1. Find the next empty cell.
2. Try numbers from 1 to 9.
3. Check if the number is valid:
   - Not in the same row
   - Not in the same column
   - Not in the same 3×3 subgrid
4. Recursively attempt to solve the rest of the board.
5. If no number works, backtrack to the previous step.

### Time Complexity

Worst case complexity:

O(9^(n))

where n is the number of empty cells.

However, pruning through Sudoku constraints significantly reduces the search space in practice.

---

## Solver Flow

Start
  │
  ▼
Find empty cell
  │
  ▼
Try number 1-9
  │
  ▼
Is valid?
 ├─ No → try next number
 │
 └─ Yes
      │
      ▼
  Recurse solve
      │
      ▼
Solved?
 ├─ Yes → Done
 └─ No → Backtrack

---

## Future Improvements

* Sudoku puzzle generator
* Difficulty classification
* GUI or visualizer
