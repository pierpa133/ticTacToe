#include "game.hpp"

int main()
{
    bool Rematch = 1;

    while (Rematch)
    {
        game *TicTacToe = new game;

        while (TicTacToe->isRunning())
            TicTacToe->Loop();

        Rematch = TicTacToe->getRematch();
             

        delete TicTacToe;
    }

    return 0;
}