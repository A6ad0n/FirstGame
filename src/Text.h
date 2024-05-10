#pragma once

#include "Consts.h"

class Text final
{
public:
    //Contsructors and Destructors
    Text();
    Text(const sf::Font &font, const unsigned int &ID, const unsigned int &characterSize, const sf::Color &color);
    ~Text();

    void spawn(const sf::Vector2f &position, const std::string &message);

    void update(const std::vector<int*> &info);
    void render(sf::RenderTarget* target) const;

private:
    std::vector<sf::Text*> texts;
    sf::Text* text;

    sf::Font font;
    unsigned int ID;
    unsigned int characterSize;
    sf::Color color;
};