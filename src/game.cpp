#include <iostream>
#include <cstring>

#include "game.hpp"
#include "button.hpp"

using namespace sf;

game::game() :
    Window(VideoMode({600, 600}), "Tic Tac Toe", Style::Titlebar | Style::Close),

    BackgroundTex(Vector2u({600, 600})),
    Background(BackgroundTex),
    
    CircleTex(Vector2u({100, 100})),
    
    CrossTex(Vector2u({100, 100})),

    Enemy(Grid),

    Roboto("../res/robotoRegular.ttf"),
    RematchButton("Rematch?", 100, 50, 250, 250, Roboto),

    WinText(Roboto),

    Running(1),
    Win(0),
    RematchVar(0),
    Turn(1),
    OldTurn(Turn)
{
    //GRID_INIT//
    memset(Grid, 0, sizeof(Grid));

    //TEXTURES_INIT//
    if (!CircleTex.loadFromFile("../res/circle.png")) { std::cerr << "ERROR: can't load the texture" << std::endl; }
    if (!CrossTex.loadFromFile("../res/cross.png")) { std::cerr << "ERROR: can't load the texture" << std::endl; }

    if (!BackgroundTex.loadFromFile("../res/background.png")) { std::cerr << "ERROR: can't load the texture" << std::endl; }
    Background.setPosition(Vector2f({0, 0}));

    //TEXTS_INIT//
    WinText.setPosition({ 0.0f, 0.0f });
    WinText.setFillColor(Color::Blue);

    std::cout << "Game started" << std::endl;
}

game::~game() 
{ 
    Window.close();
    
    std::cout << "Game ended" << std::endl;
}

void game::Loop()
{
    //---EVENT-LISTENER---//
    while (const std::optional event = Window.pollEvent())
    {
        //window closed
        if (event->is<Event::Closed>()) { Running = 0; }

        //mouse click
        if (event->is<Event::MouseButtonReleased>()) 
        { 
            PlayerHit();

            Rematch(); 
        }
    }

    TurnSwitch();

    EnemyHit();

    Render();
    
}

void game::PlayerHit()
{
    //PLAYER HIT//
    //the hit is done if the game hasn't been finished yet 
    //if the hit is accomplished change the turn
    if (Turn && !Win && hit(Mouse::getPosition(Window).x, Mouse::getPosition(Window).y)) { Turn = !Turn; } 
}

void game::Rematch()
{
    //CHECK REMATCH//
    if (Win != 0)
    {
        RematchVar = checkRematch(Mouse::getPosition(Window).x, Mouse::getPosition(Window).y);
        if (RematchVar) { Running = false; }
    }
}

void game::TurnSwitch()
{
    //TURN SWITCH(in the middle of the hits)//
    if (OldTurn != Turn)
    {
        Win = checkWin();

        if (Win > 0)
        {
            if (Win == 1) { WinText.setString("CIRCLE WON!"); std::cout << "CIRCLE WON!" << std::endl; }
            if (Win == 2) { WinText.setString("CROSS WON!"); std::cout << "CROSS WON!" << std::endl; }
            if (Win == 4) { WinText.setString("TIE!"); std::cout << "TIE!" << std::endl; }
        }

        //switch turn
        OldTurn = Turn;

        printGrid();
    }
}

void game::EnemyHit()
{
    //ENEMY HIT//
    if (!Win && !Turn)
    {
        std::vector<int> hit = Enemy.toWin();

        if (hit[0] == -1)
            hit = Enemy.blockWin();

        if (hit[0] == -1)
            hit = Enemy.makeMove();
        
        if (hit[0] == -1)
            hit = Enemy.randMove();

        Grid[hit[0]][hit[1]] = 2;

        Turn = !Turn;
    }
}

void game::Render()
{
    //---RENDER---//
    gridConvert();
    
    Window.clear(Color::White);
    
        Window.draw(Background);

        gridRender();

        if(Win != 0) 
        { 
            RematchButton.drawButton(&Window); 
            Window.draw(WinText);
        }

    Window.display();
}

bool game::hit(int x, int y)
{
    int a = 0; //to don't make crash the program due to the last if
    int *hittedSpot = &a;

    //find the hitted spot
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if ((y > i*200 && y < (i*200)+200)  &&  (x > j*200 && x < (j*200)+200))   { hittedSpot = &Grid[i][j]; }
        }
    }
    
    //check if already picked
    if (*hittedSpot != 0) { return false; }

    //assign the value to it
    if(Turn) { *hittedSpot = 1; }
    else { *hittedSpot = 2; }

    if (!a) { return true; }
    else { return false; }
}

int game::checkWin()
{
    //diagonals check
        //circle checks
        if (Grid[0][0] == 1 && Grid[1][1] == 1 && Grid[2][2] == 1) { return 1; }
        if (Grid[0][2] == 1 && Grid[1][1] == 1 && Grid[2][0] == 1) { return 1; }

        //cross checks
        if (Grid[0][0] == 2 && Grid[1][1] == 2 && Grid[2][2] == 2) { return 2; }
        if (Grid[0][2] == 2 && Grid[1][1] == 2 && Grid[2][0] == 2) { return 2; }
    
    for (int i = 0; i < ROWS; i++)
    {
        //row check
            //circle check
            if (Grid[i][0] == 1 && Grid[i][1] == 1 && Grid[i][2] == 1) { return 1; }
            //cross check
            if (Grid[i][0] == 2 && Grid[i][1] == 2 && Grid[i][2] == 2) { return 2; }

        //columns check
            //circle check
            if (Grid[0][i] == 1 && Grid[1][i] == 1 && Grid[2][i] == 1) { return 1; }
            //cross check
            if (Grid[0][i] == 2 && Grid[1][i] == 2 && Grid[2][i] == 2) { return 2; }
    }

    //tie check
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (Grid[i][j] == 0) { return 0; }
        }
    }
    
    //tie
    return 4;
}

bool game::checkRematch(float x, float y)
{
    if(RematchButton.checkPressed(x, y)) { return 1; }

    return 0;
}

void game::gridConvert()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (Grid[j][i] == 1) 
            {
                //creating circle
                Gridvec.emplace_back(CircleTex);  
                //setting his position
                Gridvec.back().setPosition(Vector2f({i*200.0f+50.0f, j*200.0f+50.0f}));                     
            }
            else if (Grid[j][i] == 2)
            {
                //creating cross
                Gridvec.emplace_back(CrossTex);
                //setting his position
                Gridvec.back().setPosition(Vector2f({i*200.0f+50.0f, j*200.0f+50.0f}));  
            }
        }
    }
}

void game::gridRender()
{
    for (int i = 0; i < Gridvec.size(); i++)
    {
        Window.draw(Gridvec.at(i));
    }
}



bool game::getRematch()
{
    return RematchVar;
}

bool game::isRunning()
{
    return Running;
}

void game::printGrid()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            std::cout << Grid[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
