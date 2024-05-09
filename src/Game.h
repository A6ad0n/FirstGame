#pragma once

#include "Enemy.h"

class Game final
{
    private:
        //Variables
        //Window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;
        
        std::vector<sf::Text*> gettedPointsTexts;
        sf::Text* gettedPointsText;

        sf::Text pointsText;
        sf::Font font;

        //Game logic
        int points;
        float enemySpawnerTimer;
        bool isMouseMoved;
        int frameCount;

        //Mouse position
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        //Game objects
        std::vector<Enemy*> enemies;
        Enemy* enemy;

        //Functions
        void initVariables();
        void initWindow();
        void initTextures();
        void initEnemies();
        void initPointsText();
        void initGettedPointsText();

    public:
        //Constructors and Destructors
        Game();
        ~Game();

        //Acessors
        bool isRunning();

        //Functions
        void spawnEnemy();
        void spawnGettedPointsText(const sf::Vector2f &position, const int &ID);
        void pollEvents();

        void updateMousePos();
        void updateEnemies();
        void updatePointsText();
        void updateGettedPointsText();
        void update();

        void renderEnemies();
        void renderPointsText();
        void renderGettedPointsText();
        void render();
};