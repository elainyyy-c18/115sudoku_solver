#include "../include/sudoku.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstring>

using namespace std;

Sudoku::Sudoku() : rng((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {
    clear();
}

int Sudoku::boxId(int r, int c) const {
    return (r / 3) * 3 + (c / 3);
}

int Sudoku::popcount9(int x) const {
    return __builtin_popcount(x);
}

int Sudoku::candidateMask(int r, int c) const {
    int used = rowMask[r] | colMask[c] | boxMask[boxId(r, c)];
    return ((1 << 9) - 1) & (~used);
}

bool Sudoku::place(int r, int c, int val) {
    int bit = 1 << (val - 1);
    int b = boxId(r, c);

    if ((rowMask[r] & bit) || (colMask[c] & bit) || (boxMask[b] & bit)) {
        return false;
    }

    board[r][c] = val;
    rowMask[r] |= bit;
    colMask[c] |= bit;
    boxMask[b] |= bit;
    return true;
}

void Sudoku::removeVal(int r, int c, int val) {
    int bit = 1 << (val - 1);
    int b = boxId(r, c);

    board[r][c] = 0;
    rowMask[r] &= ~bit;
    colMask[c] &= ~bit;
    boxMask[b] &= ~bit;
}

bool Sudoku::findBestCell(int &bestR, int &bestC, int &bestMask) const {
    int minChoices = 10;
    bestR = -1;
    bestC = -1;
    bestMask = 0;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (board[r][c] != 0) continue;

            int mask = candidateMask(r, c);
            int cnt = popcount9(mask);

            if (cnt == 0) {
                bestR = r; bestC = c; bestMask = 0;
                return true; 
            }

            if (cnt < minChoices) {
                minChoices = cnt;
                bestR = r; bestC = c; bestMask = mask;
                if (cnt == 1) return true;
            }
        }
    }
    return (bestR != -1);
}

vector<int> Sudoku::maskToValues(int mask, bool shuffleOrder) {
    vector<int> vals;
    for (int d = 1; d <= 9; d++) {
        if (mask & (1 << (d - 1))) vals.push_back(d);
    }
    if (shuffleOrder) {
        shuffle(vals.begin(), vals.end(), rng);
    }
    return vals;
}

bool Sudoku::solveDfs(bool randomOrder) {
    recursiveCalls++;

    int r, c, mask;
    bool hasEmpty = findBestCell(r, c, mask);

    if (!hasEmpty) return true; 

    if (mask == 0) {
        backtracks++;
        return false;
    }

    vector<int> choices = maskToValues(mask, randomOrder);

    for (int val : choices) {
        if (place(r, c, val)) {
            assignments++;
            if (solveDfs(randomOrder)) return true;
            removeVal(r, c, val);
        }
    }

    backtracks++;
    return false;
}

void Sudoku::countSolutionsDfs(int &count, int limit) {
    if (count >= limit) return;

    int r, c, mask;
    bool hasEmpty = findBestCell(r, c, mask);

    if (!hasEmpty) {
        count++;
        return;
    }

    if (mask == 0) return;

    vector<int> choices = maskToValues(mask, false);

    for (int val : choices) {
        if (count >= limit) return;
        if (place(r, c, val)) {
            countSolutionsDfs(count, limit);
            removeVal(r, c, val);
        }
    }
}

bool Sudoku::isValidInitialBoard() {
    int tmpBoard[N][N];
    memcpy(tmpBoard, board, sizeof(board));

    fill(rowMask, rowMask + N, 0);
    fill(colMask, colMask + N, 0);
    fill(boxMask, boxMask + N, 0);

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            int val = tmpBoard[r][c];
            board[r][c] = 0;
            if (val != 0) {
                if (!place(r, c, val)) return false;
            }
        }
    }
    return true;
}

void Sudoku::clear() {
    memset(board, 0, sizeof(board));
    fill(rowMask, rowMask + N, 0);
    fill(colMask, colMask + N, 0);
    fill(boxMask, boxMask + N, 0);
    resetStats();
}

void Sudoku::resetStats() {
    recursiveCalls = assignments = backtracks = 0;
}

bool Sudoku::loadBoard(const vector<vector<int>> &input) {
    if ((int)input.size() != 9) return false;
    clear();
    for (int r = 0; r < 9; r++) {
        if ((int)input[r].size() != 9) return false;
        for (int c = 0; c < 9; c++) board[r][c] = input[r][c];
    }
    return isValidInitialBoard();
}

vector<vector<int>> Sudoku::getBoard() const {
    vector<vector<int>> res(9, vector<int>(9));
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) res[r][c] = board[r][c];
    }
    return res;
}

void Sudoku::printBoard() const {
    cout << "-------------------------\n";
    for (int r = 0; r < 9; r++) {
        cout << "| ";
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == 0) cout << ". ";
            else cout << board[r][c] << " ";
            if ((c + 1) % 3 == 0) cout << "| ";
        }
        cout << "\n";
        if ((r + 1) % 3 == 0) cout << "-------------------------\n";
    }
}

bool Sudoku::solve(bool randomOrder) {
    resetStats();
    return solveDfs(randomOrder);
}

int Sudoku::countSolutions(int limit) {
    int count = 0;
    countSolutionsDfs(count, limit);
    return count;
}

long long Sudoku::getRecursiveCalls() const { return recursiveCalls; }
long long Sudoku::getAssignments() const { return assignments; }
long long Sudoku::getBacktracks() const { return backtracks; }

bool Sudoku::generateFullSolution() {
    clear();
    return solve(true);
}

bool Sudoku::generatePuzzle(int difficulty) {
    if (!generateFullSolution()) return false;

    int cluesTarget = (difficulty == 1) ? 40 : (difficulty == 2) ? 32 : 26;
    vector<pair<int, int>> cells;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) cells.push_back({r, c});
    }
    shuffle(cells.begin(), cells.end(), rng);

    int currentClues = 81;
    for (auto [r, c] : cells) {
        if (currentClues <= cluesTarget) break;

        int backup = board[r][c];
        removeVal(r, c, backup);

        if (countSolutions(2) != 1) {
            place(r, c, backup); 
        } else {
            currentClues--;
        }
    }
    return true;
}