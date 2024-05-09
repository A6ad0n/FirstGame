#pragma once

#include "Consts.h"

class Text
{
    private:
        sf::Text text;
        sf::Vector2f position;
        sf::Font font;
        unsigned int characterSize;
        sf::Color color;

        void initText();
    public:
        Text(const sf::Font &font, const unsigned int &characterSize, const sf::Color &color);
        ~Text();

        void setPosition(const sf::Vector2f &position);

        void spawnText();
        void updateText();
        void renderText();
};