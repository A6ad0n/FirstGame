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
        sf::Text* Text;

        sf::Text pointsText;
        sf::Font font;

        //Game logic
        int points;
        int strength;
        int costStrength;
        float enemySpawnerTimer;
        
        bool isMouseMoved;
        bool mouseButtonPressed;
        bool isDebug;
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
        void initText();

    public:
        //Constructors and Destructors
        Game();
        ~Game();

        //Acessors
        bool isRunning();

        //Functions
        void spawnEnemy();
        void spawnText(const sf::Vector2f &position, const std::string &text);
        void spawnUpgradeText();
        void pollEvents();

        void updateMousePos();
        void updateEnemies();
        void updatePointsText();
        void updateText();
        void update();

        void renderEnemies();
        void renderPointsText();
        void renderText();
        void render();
};