#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Game
{
    private:
        //Variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;

        sf::Sprite enemy;
        sf::Texture enemyTexture;

        //Functions
        void initVariables();
        void initWindow();
        void initTextures();
        void initEnemies();

    public:
        //Constructors and Destructors
        Game();
        virtual ~Game();

        //Acessors
        bool isRunning();

        //Functions
        void pollEvents();
        void update();
        void render();
};