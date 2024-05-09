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
        sf::Vector2f scale;

        int cost;

        //Functions
        virtual void initID();
        virtual void initTextures();
        virtual void initSpeed();
        virtual void initScale();
        virtual void initCost();

        void initVariables();
        void initSpeed(const int &a, const int &b);

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

        //Functions
        void spawn(const sf::VideoMode &videomode);
        void spawn(const float &x, const float &y);
        void spawn(const sf::Vector2f &position);
        void move();
        bool contains(const sf::Vector2f &point);
        bool inTargetWindow(sf::RenderTarget* target);

        void render(sf::RenderTarget* target);
};