#include <iostream>

#include "button.hpp"

using namespace sf;

button::button(std::string text, int widht, int height, float posX, float posY, const sf::Font &font) : 
Rectangle(),

RectText(font),

Text(text), 

Widht(widht), 
Height(height),

PosX(posX), 
PosY(posY)
{
    //setting the rectangle
    Rectangle.setSize(sf::Vector2f(Widht, Height)); //size
    Rectangle.setPosition(Vector2f({ PosX, PosY }));  //position
    Rectangle.setOutlineThickness(-2.0f);   //outline
    Rectangle.setOutlineColor(sf::Color::Black);    //outline

    //setting the text  
    RectText.setPosition(Vector2f({ PosX+(Widht/4), PosY+(Height/4) })); //position
    RectText.setCharacterSize(10);  //size
    RectText.setString(Text);   //text
    RectText.setFillColor(sf::Color::Black);    //color
}


bool button::checkPressed(float x, float y)
{
    if ((x >= PosX && x <= (PosX+Widht)) && (y >= PosY && y <= (PosY+Height)))
    {
        std::cout << "Button " << Text << " PRESSED" << std::endl;
        return 1;
    }
    else   
        return 0;
}

void button::drawButton(sf::RenderWindow *window)
{
    //drawing
    window->draw(Rectangle);
    window->draw(RectText);
}

void button::setPos(float posX, float posY)
{
    PosX = posX;
    PosY = posY;
    Rectangle.setPosition(Vector2f({ PosX, PosY }));  
    RectText.setPosition(Vector2f({ PosX+(Widht/4), PosY+(Height/4) })); 
}
