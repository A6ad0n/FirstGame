#include "Game.h"

void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode = sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow(this->videoMode, "First Game", sf::Style::Default);
    this->window->setFramerateLimit(144);
}

void Game::initTextures()
{
    this->enemyTexture.loadFromFile("sprites/craftpix-net-354073-free-emoji-icons-for-rpg-games/PNG/without background/1.png");
}

void Game::initEnemies()
{
    this->enemy.setPosition(sf::Vector2f(100.0f, 100.0f));
    this->enemy.setTexture(this->enemyTexture);
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initTextures();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

bool Game::isRunning()
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::KeyPressed:
                switch (this->event.key.code)
                {
                    case sf::Keyboard::Escape:
                        this->window->close();
                        break;

                    default:
                        break;
                }
            
            default:
                break;
        }
    }
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    this->window->clear(sf::Color::Cyan);

    this->window->draw(this->enemy);

    this->window->display();
}