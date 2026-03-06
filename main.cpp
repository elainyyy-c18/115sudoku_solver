#include <iostream>
#include <vector>
#include "include/sudoku.h"

using namespace std;

void printMenu() {
    cout << "\n=== Sudoku Project ===\n";
    cout << "1. Solve a Sudoku puzzle\n";
    cout << "2. Generate a Sudoku puzzle\n";
    cout << "3. Exit\n";
    cout << "Choose: ";
}

vector<vector<int>> readBoardFromInput() {
    vector<vector<int>> input(9, vector<int>(9));
    cout << "Please enter the Sudoku board (9 lines, 9 integers each, 0 means empty):\n";
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            cin >> input[r][c];
        }
    }
    return input;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Sudoku sdk;

    while (true) {
        printMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            auto input = readBoardFromInput();
            if (!sdk.loadBoard(input)) {
                cout << "Invalid Sudoku board.\n";
                continue;
            }
            cout << "\nInput puzzle:\n";
            sdk.printBoard();

            if (sdk.solve(false)) {
                cout << "\nSolved board:\n";
                sdk.printBoard();
                cout << "Solver statistics:\n";
                cout << "Recursive calls: " << sdk.getRecursiveCalls() << "\n";
                cout << "Assignments:     " << sdk.getAssignments() << "\n";
                cout << "Backtracks:      " << sdk.getBacktracks() << "\n";
            } else {
                cout << "No solution found.\n";
            }
        }
        else if (choice == 2) {
            cout << "Choose difficulty (1=easy, 2=medium, 3=hard): ";
            int diff;
            cin >> diff;
            if (diff < 1 || diff > 3) diff = 2;

            if (!sdk.generatePuzzle(diff)) {
                cout << "Failed to generate puzzle.\n";
                continue;
            }

            cout << "\nGenerated puzzle:\n";
            sdk.printBoard();

            Sudoku solverCopy;
            solverCopy.loadBoard(sdk.getBoard());
            solverCopy.solve(false);

            cout << "\nOne valid solution:\n";
            solverCopy.printBoard();
            cout << "Solution statistics:\n";
            cout << "Recursive calls: " << solverCopy.getRecursiveCalls() << "\n";
            cout << "Assignments:     " << solverCopy.getAssignments() << "\n";
            cout << "Backtracks:      " << solverCopy.getBacktracks() << "\n";
        }
        else if (choice == 3) {
            cout << "Bye!\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}