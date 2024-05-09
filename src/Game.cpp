#include "Game.h"

void Game::initVariables()
{
    this->window = nullptr;

    this->enemySpawnerTimer = 0.f;
    this->points = 0;
    this->isMouseMoved = false;
    this->frameCount = 0;

    this->font.loadFromFile("resources/fonts/Dudka Regular.ttf");
}

void Game::initWindow()
{
    //this->videoMode = sf::VideoMode(400, 500);
    this->videoMode = sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow(this->videoMode, "First Game", sf::Style::Default);
    this->window->setFramerateLimit(144);
}

void Game::initTextures()
{
}

void Game::initEnemies()
{
    this->enemy = nullptr;
}

void Game::initPointsText()
{
    this->pointsText.setPosition(10.f, 10.f);
    this->pointsText.setFont(this->font);
    this->pointsText.setCharacterSize(24);
    this->pointsText.setFillColor(sf::Color::Black);
}

void Game::initGettedPointsText()
{
    this->gettedPointsText->setFont(this->font);
    this->gettedPointsText->setCharacterSize(50);
    this->gettedPointsText->setFillColor(sf::Color::Red);
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initTextures();
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
    this->enemy = new Enemy();
    this->enemy->setPosition(sf::Vector2f(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x)),
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x))
    ));
    this->enemy->setScale(sf::Vector2f(0.15f, 0.15f));
    this->enemies.push_back(this->enemy);
}

void Game::spawnGettedPointsText(const sf::Vector2f &position, const int &ID)
{
    this->gettedPointsText = new sf::Text();
    this->initGettedPointsText();
    this->gettedPointsText->setPosition(
        position.x,
        position.y
    );
    this->gettedPointsText->setString(std::to_string(ID));
    this->gettedPointsTexts.push_back(this->gettedPointsText);

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
    if (this->enemies.size() < Consts::maxEnemies)
    {
        if (this->enemySpawnerTimer >= Consts::enemySpawnerTimerMax)
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
        this->enemies[i]->move();

        if (this->isMouseMoved && this->enemies[i]->contains(this->mousePosView))
        {
            deleted = true;
            this->points += enemies[i]->getID();
            spawnGettedPointsText(mousePosView, enemies[i]->getID());
        }

        if (this->enemies[i]->getPosition().y > this->window->getSize().y ||
            this->enemies[i]->getPosition().y < - (this->enemies[i]->getSize().y) ||
            this->enemies[i]->getPosition().x > this->window->getSize().x ||
            this->enemies[i]->getPosition().x < - (this->enemies[i]->getSize().x))
            deleted = true;
        
        if (deleted)
        {
            delete this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
            deleted = false;
        }
    }
}

void Game::updatePointsText()
{
    this->pointsText.setString("Points: " + std::to_string(this->points) + 
    "\nx: " + std::to_string(this->mousePosWindow.x) + 
    " y: " + std::to_string(this->mousePosWindow.y) +
    "\nx: " + std::to_string(static_cast<int>(this->mousePosView.x)) +
    " y: " + std::to_string(static_cast<int>(this->mousePosView.y)) +
    "\nFrame: " + std::to_string(this->frameCount / 60));
}

void Game::updateGettedPointsText()
{
    if (this->frameCount % 3 == 0)
    {
        for (size_t i{}; i < gettedPointsTexts.size(); ++i)
        {
            if (gettedPointsTexts[i]->getCharacterSize() < 5)
            {
                delete this->gettedPointsTexts[i];
                this->gettedPointsTexts.erase(this->gettedPointsTexts.begin() + i);
            }
            else
                gettedPointsTexts[i]->setCharacterSize(gettedPointsTexts[i]->getCharacterSize() * 0.95f);
        }
    }
}

void Game::update()
{
    this->pollEvents();

    this->updateMousePos();

    this->updateEnemies();

    this->updatePointsText();

    this->updateGettedPointsText();
}

void Game::renderEnemies()
{
    for (auto &e : enemies)
        this->window->draw(e->getSprite());
}

void Game::renderPointsText()
{
    this->window->draw(this->pointsText);
}

void Game::renderGettedPointsText()
{
    for (auto t : gettedPointsTexts)
        this->window->draw(*t);
}

void Game::render()
{
    this->window->clear(sf::Color::Cyan);

    this->renderEnemies();

    this->renderPointsText();

    this->renderGettedPointsText();

    this->window->display();

    ++this->frameCount;
}