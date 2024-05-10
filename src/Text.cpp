#include "Text.h"

Text::Text()
{
}

Text::Text(const sf::Font &font, const unsigned int& ID, const unsigned int &characterSize, const sf::Color &color) : 
font(font), ID(ID), characterSize(characterSize), color(color)
{
}

Text::~Text()
{
    for (size_t i{}; i < texts.size(); ++i)
        delete texts[i];
}

void Text::spawn(const sf::Vector2f &position, const std::string &message)
{
    text = new sf::Text();
    text->setCharacterSize(characterSize);
    text->setFont(font);
    text->setFillColor(color);
    text->setPosition(position.x, position.y);
    text->setString(message);
    texts.push_back(text);
}

void Text::update(const std::vector<int*> &info)
{
    for (size_t i{}; i < texts.size(); ++i)
    {
        switch (ID)
        {
        case 0: //GUI text
        {
            text->setString("Points: " + std::to_string(*info[1]) + 
            "\nStrength: " + std::to_string(*info[2]) +
            "\nUpgrade strength costs: " + std::to_string(*info[3]));
            break;
        }
        case 1: //Getted points text
        {
            if (*info[0] % 3 == 0)
            {
                if (texts[i]->getCharacterSize() < 5)
                {
                    delete texts[i];
                    texts.erase(texts.begin() + i);
                }
                else
                    texts[i]->setCharacterSize(texts[i]->getCharacterSize() * 0.95f);
            }
            break;
        }
        case 2: //Upgrade text
        {
            if (*info[0] % 5 == 0)
            {
                if (texts[i]->getCharacterSize() < 20)
                {
                    delete texts[i];
                    texts.erase(texts.begin() + i);
                }
                else
                    texts[i]->setCharacterSize(texts[i]->getCharacterSize() * 0.95f);
            }
        }
        default:
            break;
        }
    }
}

void Text::render(sf::RenderTarget* target) const
{
    for (auto t : texts)
        target->draw(*t);
}


