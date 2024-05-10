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

void Text::update(const GameInfo &info)
{
    for (size_t i{}; i < texts.size(); ++i)
    {
        switch (ID)
        {
        case 0: //GUI text
        {
            std::string out = "Points: " + std::to_string(info.points) + 
            "\nStrength: " + std::to_string(info.strength) +
            "\nUpgrade strength costs: " + std::to_string(info.costStrength) +
            "\nTo upgrade press UP";
            if (info.isDebug)
                out += "\nFrameCount: " + std::to_string(info.frameCount);
            texts[i]->setString(out);
            break;
        }
        case 1: //Getted points text
        {
            if (info.frameCount % 3 == 0)
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
            if (info.frameCount % 5 == 0)
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


