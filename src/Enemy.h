#pragma once

#include "Consts.h"

class Enemy
{
    private:
        //Variables
        int ID;
        sf::Sprite enemy;
        sf::Texture enemyTexture;

        sf::Vector2f speed;

        int cost;

        //Functions
        void initID();
        void initTextures();
        void initVariables();
        void initSpeed(const int a, const int b);
        

    protected:

    public:
        //Constructors and destructors
        Enemy();
        virtual ~Enemy();

        //Setters
        void setPosition(const sf::Vector2f &position);
        void setScale(const sf::Vector2f &factors);

        //Getters
        int getID();
        sf::Vector2f getSize();
        sf::Vector2f getPosition();
        sf::Sprite getSprite();

        //Functions
        void move();
        bool contains(const sf::Vector2f &point);
};