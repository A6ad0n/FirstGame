#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <ctime>

class Game
{
    private:
        //Variables
        //Window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;
        
        sf::Text pointsText;
        sf::Font font;

        //Game logic
        int points;
        float enemySpawnerTimer;
        float enemySpawnerTimerMax;
        size_t maxEnemies;
        bool isMouseMoved;

        //Mouse position
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        //Game objects
        std::vector<sf::Sprite> enemies;
        sf::Sprite enemy;
        sf::Texture enemyTexture;

        //Functions
        void initVariables();
        void initWindow();
        void initTextures();
        void initEnemies();
        void initPointsText();

    public:
        //Constructors and Destructors
        Game();
        virtual ~Game();

        //Acessors
        bool isRunning();

        //Functions
        void spawnEnemy();
        void pollEvents();

        void updateMousePos();
        void updatePointsText();
        void updateEnemies();
        void update();

        void renderPointsText();
        void renderEnemies();
        void render();
};