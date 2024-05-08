#include "Game.h"

void Game::initVariables()
{
    this->window = nullptr;

    this->maxEnemies = 5;
    this->enemySpawnerTimerMax = 100.f;
    this->enemySpawnerTimer = this->enemySpawnerTimerMax;
    this->points = 0;
    this->isMouseMoved = false;

    this->font.loadFromFile("fonts/Dudka Regular.ttf");
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
    this->enemy.setPosition(0.0f, 0.0f);
    this->enemy.setTexture(this->enemyTexture);
}

void Game::initPointsText()
{
    this->pointsText.setPosition(10.f, 10.f);
    this->pointsText.setFont(this->font);
    this->pointsText.setCharacterSize(24);
    this->pointsText.setFillColor(sf::Color::Black);
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initTextures();
    this->initEnemies();
    this->initPointsText();
}

Game::~Game()
{
    delete this->window;
}

bool Game::isRunning()
{
    return this->window->isOpen();
}

void Game::spawnEnemy()
{
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getGlobalBounds().getSize().x)),
        0.f
    );
    this->enemy.setTexture(this->enemyTexture);
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemies.push_back(this->enemy);
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
            
            case sf::Event::MouseMoved:
            {
                sf::Vector2i prevMousePosition = this->mousePosWindow;
                sf::Vector2i currentMousePosition = sf::Mouse::getPosition(*this->window);

                if (currentMousePosition != prevMousePosition)
                    this->isMouseMoved = true;
                else
                    this->isMouseMoved = false;

                break;
            }
            
            default:
                break;
        }
    }
}

void Game::updateMousePos()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}



void Game::updateEnemies()
{
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnerTimer >= this->enemySpawnerTimerMax)
        {
            this->spawnEnemy();
            this->enemySpawnerTimer = 0.f;
        }
        else
            this->enemySpawnerTimer += 1.f;
    }

    //move
    bool deleted{};
    for (size_t i{}; i < enemies.size(); ++i)
    {
        this->enemies[i].move(sf::Vector2f(0.f, 1.f));

        if (this->isMouseMoved && this->enemies[i].getGlobalBounds().contains(this->mousePosView))
        {
            deleted = true;
            ++this->points;
        }

        if (this->enemies[i].getPosition().y > this->window->getSize().y)
            deleted = true;
        
        if (deleted)
        {
            this->enemies.erase(this->enemies.begin() + i);
            deleted = false;
        }
    }
}

void Game::updatePointsText()
{
    this->pointsText.setString("Points: " + std::to_string(this->points));
}

void Game::update()
{
    this->pollEvents();

    this->updateMousePos();

    this->updateEnemies();

    this->updatePointsText();
}

void Game::renderPointsText()
{
    this->window->draw(this->pointsText);
}

void Game::renderEnemies()
{
    for (auto &e : enemies)
        this->window->draw(e);
}

void Game::render()
{
    this->window->clear(sf::Color::Cyan);

    this->renderEnemies();

    this->renderPointsText();

    this->window->display();
}