#pragma once

#include <SFML/Graphics.hpp>
#include "button.hpp"
#include "enemy.hpp"

using namespace sf;

#define ROWS 3
#define COLUMNS 3

class game
{
public:
    game();

    ~game();

    void Loop();

    bool getRematch();

    bool isRunning();

private:
    RenderWindow Window;

    Texture BackgroundTex;
    Sprite Background;

    Texture CircleTex;

    Texture CrossTex;

    bool Running;

    int Win;

    bool RematchVar;

    bool Turn;      //1: O      0: X

    bool OldTurn;

    int Grid[ROWS][COLUMNS]; //0: empty      1: O        2: X 
    std::vector <Sprite> Gridvec;  

    enemy Enemy;

    Font Roboto;
    button RematchButton;

    Text WinText;

    //Private Methods

    void PlayerHit();

    void Rematch();

    void TurnSwitch();

    void EnemyHit();

    void Render();

    bool checkRematch(float x, float y);

    void gridRender();

    void gridConvert();

    int checkWin();

    bool hit(int x, int y);

    void printGrid();
};


