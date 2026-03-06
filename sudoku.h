#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <random>

class Sudoku {
private:
    static const int N = 9;
    int board[N][N];
    int rowMask[N], colMask[N], boxMask[N];

    long long recursiveCalls;
    long long assignments;
    long long backtracks;

    std::mt19937 rng;

    int boxId(int r, int c) const;
    int popcount9(int x) const;
    int candidateMask(int r, int c) const;
    bool place(int r, int c, int val);
    void removeVal(int r, int c, int val);
    bool findBestCell(int &bestR, int &bestC, int &bestMask) const;
    std::vector<int> maskToValues(int mask, bool shuffleOrder);
    bool solveDfs(bool randomOrder);
    void countSolutionsDfs(int &count, int limit);
    bool isValidInitialBoard();
    bool generateFullSolution();

public:
    Sudoku();
    void clear();
    void resetStats();
    bool loadBoard(const std::vector<std::vector<int>> &input);
    std::vector<std::vector<int>> getBoard() const;
    void printBoard() const;
    bool solve(bool randomOrder = false);
    int countSolutions(int limit = 2);
    long long getRecursiveCalls() const;
    long long getAssignments() const;
    long long getBacktracks() const;
    bool generatePuzzle(int difficulty);
};

#endif // SUDOKU_H