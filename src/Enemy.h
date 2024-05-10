#pragma once

#include "Consts.h"

class Enemy
{
    public:
        //Constructors and destructors
        Enemy();
        virtual ~Enemy();

        //Setters
        void setScale(const sf::Vector2f &factors);

        //Getters
        int getID() const;

        //Functions
        void spawn(const sf::VideoMode &videomode);
        void spawn(const float &x, const float &y);
        void spawn(const sf::Vector2f &position);

        void move();

        bool contains(const sf::Vector2f &point) const;
        bool contains(const float &x, const float &y) const;
        
        bool inTargetWindow(sf::RenderTarget* target) const;

        void render(sf::RenderTarget* target) const;

    private:
        //Variables
        int ID;
        sf::Sprite enemy;
        sf::Texture enemyTexture;

        sf::Vector2f prevSpeed;
        sf::Vector2f speed;
        sf::Vector2f scale;

        int cost;

        //Functions
        virtual void initID();
        virtual void initTextures();
        virtual void initSpeed();

        void initVariables();
        void initSpeed(const int &a, const int &b);
};