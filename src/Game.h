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
    void playMusic();
    bool isRunning() const;

    //Functions
    void update();
    void render();
private:
    bool gameCondition;

    //Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;

    sf::Music music;

    sf::SoundBuffer buffer;
    sf::Sound sound;

    sf::Sprite background;
    sf::Texture bgTexture;
    sf::RectangleShape bgGUIText;

    sf::CircleShape target1;
    sf::CircleShape target2;

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
    void initBackground();
    void initTargets();
    void initSounds();
};