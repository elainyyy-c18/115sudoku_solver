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

This project uses a **backtracking algorithm** to solve Sudoku puzzles.

The solver works by filling empty cells one by one.
For each empty cell, it tries numbers from **1 to 9** and checks whether the placement is valid according to Sudoku rules:

* The number must not already appear in the same **row**
* The number must not appear in the same **column**
* The number must not appear in the same **3×3 subgrid**

If a placement is valid, the algorithm recursively continues solving the rest of the puzzle.
If no number works, the algorithm **backtracks** to the previous step and tries a different number.

---

## Future Improvements

* Sudoku puzzle generator
* Difficulty classification
* GUI or visualizer
