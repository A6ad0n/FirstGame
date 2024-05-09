#include "Text.h"

void Text::initText()
{
    this->text.setFont(this->font);
    this->text.setCharacterSize(this->characterSize);
    this->text.setFillColor(this->color);
}

Text::Text(const sf::Font &font, const unsigned int &characterSize, const sf::Color &color) : font(font), characterSize(characterSize), color(color)
{
    this->initText();
}

Text::~Text()
{
}

void Text::setPosition(const sf::Vector2f &position)
{
    this->position = position;
}


