#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game
{
    private:
        //Variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;

        //Functions
        void initVariables();
        void initWindow();

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