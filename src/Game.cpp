#include "Game.h"

void Game::initVariables()
{
    window = nullptr;

    enemySpawnerTimer = 0;
    points = 0;
    strength = 1;
    costStrength = 500;
    isMouseMoved = false;
    mouseButtonPressed = false;
    isDebug = false;
    frameCount = 0;

    info.push_back(&frameCount);
    info.push_back(&points);
    info.push_back(&strength);
    info.push_back(&costStrength);
}

void Game::initWindow()
{
    videoMode = sf::VideoMode::getDesktopMode();
    window = new sf::RenderWindow(videoMode, "First Game", sf::Style::Default);
    window->setFramerateLimit(144);
}

void Game::initText()
{
    sf::Font font;
    font.loadFromFile("resources/fonts/Dudka Regular.ttf");
    texts.push_back(new Text(
        font, 0, 40, sf::Color::Magenta
    ));
    texts.push_back(new Text(
        font, 1, 50, sf::Color::Red
    ));
    texts.push_back(new Text(
        font, 2, 200, sf::Color::Black
    ));
}

void Game::initGUIText()
{
    texts[0]->spawn(sf::Vector2f(15.f, 10.f), "");
}

Game::Game()
{
    initVariables();
    initWindow();
    initText();
    initGUIText();
}

Game::~Game()
{
    delete window;
    
    for (size_t i{}; i < texts.size(); ++i)
        delete texts[i];
}

bool Game::isRunning() const
{
    return window->isOpen();
}

void Game::spawnEnemy()
{
    Enemy* enemy = new Enemy();
    sf::Vector2f offset(10.f, 10.f);
    enemy->spawn(mousePosView + offset);
    enemies.push_back(enemy);
}

void Game::update()
{
    //Poll Event
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            window->close();
                            break;
                        
                        case sf::Keyboard::Up:
                            if (points >= costStrength)
                            {
                                strength += 1;
                                points -= costStrength;
                                costStrength *= 3;
                                sf::Vector2f offset(250.f, 250.f);
                                texts[2]->spawn(window->getView().getCenter() - offset, "Upgrade!");
                            }
                            break;
                        
                        case sf::Keyboard::Enter:
                            isDebug = !isDebug;
                        default:
                            break;
                    }
                
                case sf::Event::MouseMoved:
                {
                    sf::Vector2i prevMousePosition = mousePosWindow;
                    sf::Vector2i currentMousePosition = sf::Mouse::getPosition(*window);

                    if (currentMousePosition != prevMousePosition)
                        isMouseMoved = true;
                    else
                        isMouseMoved = false;

                    break;
                }

                case sf::Event::MouseButtonPressed:
                    mouseButtonPressed = true;
                    break;
                
                case sf::Event::MouseButtonReleased:
                    mouseButtonPressed = false;
                    break;
                
                default:
                    break;
            }
        }
    }

    //Update mouse position
    {
        mousePosWindow = sf::Mouse::getPosition(*window);
        mousePosView = window->mapPixelToCoords(mousePosWindow);
    }

    //Update enemies
    {
        if (mouseButtonPressed && enemies.size() < Consts::maxEnemies)
        {
            if (enemySpawnerTimer >= Consts::enemySpawnerTimerMax)
            {
                spawnEnemy();
                mouseButtonPressed = false;
                enemySpawnerTimer = 0;
            }
            else
            {
                enemySpawnerTimer += 1;
            }
        }

        //move
        bool deleted{};
        for (size_t i{}; i < enemies.size() && deleted == false; ++i)
        {
            enemies[i]->move();

            if (isMouseMoved && enemies[i]->contains(mousePosView))
            {
                deleted = true;
                points += enemies[i]->getID() * strength;
                texts[1]->spawn(mousePosView, std::to_string(enemies[i]->getID() * strength));
            }

            if (enemies[i]->inTargetWindow(window))
                deleted = true;
            
            if (deleted)
            {
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                deleted = false;
            }
        }
    }

    //Update texts
    {
    for (auto t : texts)
        t->update(info);
    }
}

void Game::render()
{
    window->clear(sf::Color::Cyan);

    //render Enemies
    {
        for (auto e : enemies)
            e->render(window);
    }

    //render Texts
    {
        for (auto t : texts)
            t->render(window);
    }

    window->display();

    ++frameCount;
}