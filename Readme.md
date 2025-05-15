# 🧠 Sudoku Solver using Backtracking (C Language)

A command-line Sudoku Solver built in **pure C**, using **recursive backtracking** and full support for **dynamic grid sizes** (like 4x4, 9x9, 16x16). Includes input validation, timer, file input, and an interactive CLI menu.

---

## 📌 Features

- ✅ Solve standard 9x9 Sudoku puzzles  
- ✅ Support for **NxN boards** (N must be a perfect square like 4, 9, 16)  
- ✅ Input grid via `input.txt` file  
- ✅ Detect duplicate values in initial board  
- ✅ Track **solve time** using CPU clock  
- ✅ CLI-based menu to interact and test  
- ✅ Memory safe – handles dynamic allocation and deallocation  

---

## 🧪 Sample Demo

```
=== Sudoku Solver ===
1. Load and Solve Sudoku
2. Print Current Grid
3. Exit
4. Clear Puzzle
Enter your choice: 1

Initial Puzzle:
+---+---+---+---+---+---+---+---+---+
| 5  3  . | .  7  . | .  .  . |
| 6  .  . | 1  9  5 | .  .  . |
...

✅ Solved in 0.0010 seconds.
```

---

## 📂 Input Format (`input.txt`)

- First line = Grid size `N` (example: `9`)
- Next N lines = space-separated numbers `0–N` (use `0` for empty cells)

### Example: `input.txt`
```
9
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
```

---

## ⚙️ Compilation & Execution

### 🛠️ Compile:
```bash
gcc sudokuSolver.c -o sudokuSolver -lm
```

### ▶️ Run:
```bash
./sudokuSolver
```

---

## 🧠 Concepts Used

- 2D arrays and dynamic memory allocation
- Recursive backtracking
- File I/O (`fopen`, `fscanf`)
- Time measurement with `clock_t`
- CLI interface and safe memory handling
- Sudoku validity logic (row, column, box)

---

## 📁 Project Structure

```
├── sudokuSolver.c       // Main program
├── input.txt            // Test grid input
└── README.md            // Project documentation
```

---

## ✅ What Makes It Resume-Worthy?

- Written in **pure C** (no libraries)
- Demonstrates **DSA + systems-level** understanding
- Uses **backtracking**, recursion, memory management, file handling
- Scalable and robust

---

## 📌 Possible Extensions

- Puzzle Generator
- Difficulty level tagging
- Visual version using graphics (SDL or ncurses)
- Web-based frontend using Python/CGI
