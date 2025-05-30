#include "enemy.hpp"

#include <random>
#include <time.h>
#include <iostream>

enemy::enemy(const int (&grid)[ROWS][COLUMNS])
: Grid(grid)
{ }

bool enemy::checkRow(int row, int twoOf, int oneOf)
{
    int twos = 0;
    int ones = 0;

    for (int i = 0; i < ROWS; i++)
    {
        if (Grid[row][i] == twoOf) twos++;
        else if (Grid[row][i] == oneOf) ones++;
    }

    if (twos == 2 && ones == 1) return true;
    else return false;
}

bool enemy::checkCol(int col, int twoOf, int oneOf)
{
    int twos = 0;
    int ones = 0;

    for (int i = 0; i < ROWS; i++)
    {
        if (Grid[i][col] == twoOf) twos++;
        else if (Grid[i][col] == oneOf) ones++;
    }

    if (twos == 2 && ones == 1) return true;
    else return false;
}

bool enemy::checkDiag(bool diag, int twoOf, int oneOf)
{
    int twos = 0;
    int ones = 0;

    if (!diag)
    {
        for (int i = 0; i < ROWS; i++)
        {
            if (Grid[i][i] == twoOf) twos++;
            else if (Grid[i][i] == oneOf) ones++;
        }
    }
    else
    {
        for (int i = 0; i < ROWS; i++)
        {
            if (Grid[i][2-i] == twoOf) twos++;
            else if (Grid[i][2-i] == oneOf) ones++;
        }
    }

    if (twos == 2 && ones == 1) return true;
    else return false;
}

std::vector<int> enemy::findNeigh(const std::vector<int> &pos, int checked[ROWS][COLUMNS], int target)
{
    //returns the coords of a target element near the given element 
    for (int i = -1; i < ROWS; i+= 2)
    {
        //first check: the position must not go out of the matrix
        //second check: it must be equal to the target
        //third check: it must be not checked (==3 in the checked matrix)
        int m = pos[0];
        int n = pos[1];

        //in row
        if ((m+i >= 0 && m+i  < ROWS) && (Grid[m+i][n] == target) &&
            (checked[m+i][n] != 3))

            return std::vector<int>{ m + i, n };
        
        //in column
        if ((n+i >= 0 && n+i < COLUMNS) && (Grid[m][n+i] == target) &&
            (checked[m][n+i] != 3))

            return std::vector<int>{ m, n+i };

        //in diagonal \ //
        if (((m+i >= 0 && m+i < ROWS)&&(n+i >= 0 && n+i < COLUMNS)) && 
            (Grid[m+i][n+i] == target) && (checked[m+i][n+i] != 3))

            return std::vector<int>{ m + i, n + i };
        
        //in diagonal / //
        if (((m+i >= 0 && m+i < ROWS)&&(n+i >= 0 && n+i < COLUMNS)) && 
            (Grid[m+i][n-i] == target) && (checked[m+i][n-i] != 3))

            return std::vector<int>{ m + i, n - i };
    }

    return { -1, -1 };
}

std::vector<int> enemy::toWin()
{
    //returns the coords of the winning move

    //ROW
    for (int i = 0; i < ROWS; i++)
    {
        if (checkRow(i, 2, 0))
        {
            for (int j = 0; j < ROWS; j++)
            {
                if (Grid[i][j] == 0) return std::vector<int>{i , j};
            }
        }
    }
    
    //COLUMNS
    for (int i = 0; i < COLUMNS; i++)
    {
        if (checkCol(i, 2, 0))
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                if (Grid[j][i] == 0) return std::vector<int>{j , i};
            }
        }
    }

    //DIAGONALS
    if (checkDiag(0, 2, 0))
    {
        for (int i = 0; i < ROWS; i++)
        {
            if (Grid[i][i] == 0) return std::vector<int>{i , i};
        }
    }
    if (checkDiag(1, 2, 0))
    {
        for (int i = 0; i < COLUMNS; i++)
        {
            if (Grid[i][2-i] == 0) return std::vector<int>{i , 2-i};
        }
    }

    return std::vector<int>{-1 , -1};
}

std::vector<int> enemy::blockWin()
{
    //returns the coords to block
    //the enemy win

    //ROW
    for (int i = 0; i < ROWS; i++)
    {
        if (checkRow(i, 1, 0))
        {
            for (int j = 0; j < ROWS; j++)
            {
                if (Grid[i][j] == 0) return std::vector<int>{i , j};;
            }
        }
    }
    
    //COLUMNS
    for (int i = 0; i < COLUMNS; i++)
    {
        if (checkCol(i, 1, 0))
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                if (Grid[j][i] == 0) return std::vector<int>{j , i};;
            }
        }
    }

    //DIAGONALS
    if (checkDiag(0, 1, 0))
    {
        for (int i = 0; i < ROWS; i++)
        {
            if (Grid[i][i] == 0) return std::vector<int>{i , i};
        }
    }
    if (checkDiag(1, 1, 0))
    {
        for (int i = 0; i < COLUMNS; i++)
        {
            if (Grid[i][2-i] == 0) return std::vector<int>{i , 2-i};
        }
    }

    return std::vector<int>{-1 , -1};
}

std::vector<int> enemy::makeMove()
{
    //tries to build a tris
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (Grid[i][j] == 2)
            {
                int checked[ROWS][COLUMNS];
                while (true)
                {
                    //looks for an empty neighbor not already checked
                    std::vector<int> neigh = findNeigh({i, j}, checked, 0);
                    if (neigh[0] == -1) break;

                    //checks (=3) if it's impossible to tris
                    //returns the position if it's good, but not the actual neighbor
                    if (((neigh[0]+neigh[1] != 1) && (neigh[0]+neigh[1] != 3)) && checkDiag(0, 0, 2))
                    {
                        if (i+1 >= ROWS && j+1 >= COLUMNS) return std::vector<int>{neigh[0]-1, neigh[1]-1};
                        else if (i-1 < 0 && j-1 < 0) return std::vector<int>{neigh[0]+1, neigh[1]+1};
                        else return std::vector<int>{neigh[0], neigh[1]};
                    }
                    else if (((neigh[0]+neigh[1] != 1) && (neigh[0]+neigh[1] != 3)) && checkDiag(1, 0, 2))
                    {
                        if (i+1 >= ROWS && j-1 < 0) return std::vector<int>{neigh[0]-1, neigh[1]+1};
                        else if (i-1 < 0 && j+1 >= COLUMNS) return std::vector<int>{neigh[0]+1, neigh[1]-1};
                        else return std::vector<int>{neigh[0], neigh[1]};
                    }
                    else if (checkRow(neigh[0], 0, 2))
                    {
                        if (j+1 >= COLUMNS) return std::vector<int>{neigh[0], neigh[1]-1};
                        else if (j-1 < 0) return std::vector<int>{neigh[0], neigh[1]+1};
                        else return std::vector<int>{neigh[0], neigh[1]};
                    }
                    else if (checkCol(neigh[1], 0, 2))
                    {
                        if (i+1 >= ROWS) return std::vector<int>{neigh[0]-1, neigh[1]};
                        else if (i-1 < 0) return std::vector<int>{neigh[0]+1, neigh[1]};
                        else return std::vector<int>{neigh[0], neigh[1]};
                    }
                    else
                    {
                        checked[neigh[0]][neigh[1]] = 3;
                    }
                }
            }  
        }
    }

    return std::vector<int>{-1 , -1};
}

std::vector<int> enemy::randMove()
{
    //angles first
    if (Grid[1][1] == 1)
    {    
        if (Grid[2][2] == 0) return {2, 2};

        if (Grid[0][0] == 0) return {0, 0};

        if (Grid[0][2] == 0) return {0, 2};

        if (Grid[2][0] == 0) return {2, 0};
    } 
    else return {1, 1};
    
    //anywhere else
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (Grid[i][j] == 0) return {i, j};
        }
    }

    //(ERROR)
    return {-1, -1};
}
