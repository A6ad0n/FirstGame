#pragma once

#include "Enemy.h"
#include "Text.h"

class Game final
{
public:
    //Constructors and Destructors
    Game();
    ~Game();

    //Acessors
    bool isRunning() const;

    //Functions
    void update();
    void render();
private:
    //Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    
    std::vector<Text*> texts;

    GameInfo info;

    //Mouse position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Game objects
    std::vector<Enemy*> enemies;

    //Functions
    void initVariables();
    void initWindow();
    void initText();
    void initGUIText();
};