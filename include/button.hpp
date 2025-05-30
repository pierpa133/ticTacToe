#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class button
{
protected:
    RectangleShape Rectangle;

    Text RectText;

    std::string Text;

    int Widht, Height;

    float PosX, PosY;

public:
    button(std::string text, int widht, int height, float posX, float posY, const Font &font);

    void drawButton(RenderWindow *window);
    bool checkPressed(float x, float y);

    void setPos(float posX, float posY);
};