#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

int N;
int **grid;
bool puzzleLoaded = false;

// Print a formatted Sudoku grid
void printGrid() {
    int sqrtN = sqrt(N);
    printf("\n+");
    for (int i = 0; i < N; i++) printf("---+");
    printf("\n");

    for (int row = 0; row < N; row++) {
        printf("|");
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0) printf(" . ");
            else printf("%2d ", grid[row][col]);
            if ((col + 1) % sqrtN == 0) printf("|");
        }
        printf("\n");
        if ((row + 1) % sqrtN == 0) {
            printf("+");
            for (int i = 0; i < N; i++) printf("---+");
            printf("\n");
        }
    }
}

// Validate if num can be placed at grid[row][col]
bool isSafe(int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    int boxSize = sqrt(N);
    int startRow = row - row % boxSize;
    int startCol = col - col % boxSize;

    for (int r = 0; r < boxSize; r++) {
        for (int c = 0; c < boxSize; c++) {
            if (grid[startRow + r][startCol + c] == num)
                return false;
        }
    }

    return true;
}

// Recursive backtracking solver
bool solveSudoku() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= N; num++) {
                    if (isSafe(row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku())
                            return true;
                        grid[row][col] = 0;
                    }
                }
                return false; // Trigger backtracking
            }
        }
    }
    return true;
}

//Duplicate checking:
bool isValidInitialGrid() {
    int *check = (int *)calloc(N + 1, sizeof(int));

    // Row check
    for (int i = 0; i < N; i++) {
        for (int k = 1; k <= N; k++) check[k] = 0;
        for (int j = 0; j < N; j++) {
            int val = grid[i][j];
            if (val != 0 && check[val]) return false;
            check[val] = 1;
        }
    }

    // Column check
    for (int j = 0; j < N; j++) {
        for (int k = 1; k <= N; k++) check[k] = 0;
        for (int i = 0; i < N; i++) {
            int val = grid[i][j];
            if (val != 0 && check[val]) return false;
            check[val] = 1;
        }
    }

    // Box check
    int boxSize = sqrt(N);
    for (int row = 0; row < N; row += boxSize) {
        for (int col = 0; col < N; col += boxSize) {
            for (int k = 1; k <= N; k++) check[k] = 0;
            for (int i = 0; i < boxSize; i++) {
                for (int j = 0; j < boxSize; j++) {
                    int val = grid[row + i][col + j];
                    if (val != 0 && check[val]) return false;
                    check[val] = 1;
                }
            }
        }
    }

    free(check);
    return true;
}

// Read grid from input.txt and validate
bool loadGridFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening %s\n", filename);
        return false;
    }

    fscanf(fp, "%d", &N);
    if (sqrt(N) * sqrt(N) != N || N > 25) {
        printf("Unsupported grid size. Use 4, 9, or 16.\n");
        fclose(fp);
        return false;
    }

    // Allocate grid dynamically
    grid = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        grid[i] = (int *)malloc(N * sizeof(int));

    // Read values and validate range
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (fscanf(fp, "%d", &grid[i][j]) != 1 || grid[i][j] < 0 || grid[i][j] > N) {
                printf("Invalid input at [%d][%d]\n", i, j);
                fclose(fp);
                return false;
            }
        }
    }

    fclose(fp);

    // Validate no duplicates in initial board
    if (!isValidInitialGrid()) {
        printf("❌ Invalid board: Duplicate values found in row/column/box.\n");
        return false;
    }

    puzzleLoaded = true;
    return true;

}


// Free dynamically allocated memory
void freeGrid() {
    if (!puzzleLoaded) return; // Skip if nothing to free
    for (int i = 0; i < N; i++)
        free(grid[i]);
    free(grid);
    puzzleLoaded = false;
}


// CLI Menu
void menu() {
    int choice;
    while (1) {
        printf("\n=== Sudoku Solver ===\n");
        printf("1. Load and Solve Sudoku\n");
        printf("2. Print Current Grid\n");
        printf("3. Exit\n");
        printf("4. Clear Puzzle\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (loadGridFromFile("input.txt")) {
                printf("\nInitial Puzzle:\n");
                printGrid();

                clock_t start = clock();
                bool solved = solveSudoku();
                clock_t end = clock();

                if (solved) {
                    printf("\n✅ Solved in %.4f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
                    printGrid();
                } else {
                    printf("\n❌ No solution exists.\n");
                }
            }
        } else if (choice == 2) {
            if (puzzleLoaded)
                printGrid();
            else
                printf("⚠️  No puzzle loaded yet.\n");
        } else if (choice == 3) {
            if (puzzleLoaded) freeGrid();
            printf("Exiting...\n");
            break;
        } else if (choice == 4) {
            if (puzzleLoaded) {
                freeGrid();
                printf("🧹 Puzzle memory cleared.\n");
            } else {
                printf("⚠️  No puzzle to clear.\n");
            }
        } else {
            printf("❌ Invalid choice. Please try again.\n");
        }
    }
}


// This code implements a Sudoku solver with a command-line interface. It reads a Sudoku grid from a file, validates the input, and uses backtracking to solve the puzzle. The grid is printed in a formatted manner, and the program allows the user to load a new puzzle or print the current grid.


int main() {
    menu();
    return 0;
}