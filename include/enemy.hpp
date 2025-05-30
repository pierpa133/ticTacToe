#pragma once 

#include <vector>

#define ROWS 3
#define COLUMNS 3

class enemy
{
public:
    enemy(const int (&grid)[ROWS][COLUMNS]);

    std::vector<int> toWin();
    std::vector<int> blockWin();
    std::vector<int> makeMove();
    std::vector<int> randMove();
private:
    const int (&Grid)[ROWS][COLUMNS];

    bool checkRow(int row, int twoOf, int oneOf);
    bool checkCol(int col, int twoOf, int oneOf);
    bool checkDiag(bool diag, int twoOf, int oneOf);
    std::vector<int> findNeigh(const std::vector<int>& pos, int checked[ROWS][COLUMNS],
                              int target);
};

