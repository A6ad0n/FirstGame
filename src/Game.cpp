#include "Game.h"

void Game::initVariables()
{
    window = nullptr;

    info.enemySpawnerTimer = 0;
    info.points = 0;
    info.strength = 1;
    info.costStrength = 500;
    info.isMouseMoved = false;
    info.mouseButtonPressed = false;
    info.isDebug = false;
    info.frameCount = 0;
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
        font, 0, 40, sf::Color::Magenta //GUI text
    ));
    texts.push_back(new Text(
        font, 1, 50, sf::Color::Red     //Getted points text
    ));
    texts.push_back(new Text(
        font, 2, 200, sf::Color::Black  //Upgrade text
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

void Game::update()
{
    //Poll Event
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                //Exit game
                case sf::Event::Closed:
                    window->close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        //Exit game
                        case sf::Keyboard::Escape:
                            window->close();
                            break;
                        //Ugrade strength
                        case sf::Keyboard::Up:
                            if (info.points >= info.costStrength)
                            {
                                info.strength += 1;
                                info.points -= info.costStrength;
                                info.costStrength *= 3;
                                sf::Vector2f offset(250.f, 250.f);
                                texts[2]->spawn(window->getView().getCenter() - offset, "Upgrade!");
                            }
                            break;
                        //Debug mode switch
                        case sf::Keyboard::Enter:
                            info.isDebug = !info.isDebug;
                        default:
                            break;
                    }
                
                case sf::Event::MouseMoved:
                {
                    sf::Vector2i prevMousePosition = mousePosWindow;
                    sf::Vector2i currentMousePosition = sf::Mouse::getPosition(*window);

                    if (currentMousePosition != prevMousePosition)
                        info.isMouseMoved = true;
                    else
                        info.isMouseMoved = false;

                    break;
                }

                case sf::Event::MouseButtonPressed:
                    info.mouseButtonPressed = true;
                    break;
                
                case sf::Event::MouseButtonReleased:
                    info.mouseButtonPressed = false;
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
        if (info.mouseButtonPressed && enemies.size() < Consts::maxEnemies)
        {
            //Spawn enemy
            Enemy* enemy = new Enemy();
            sf::Vector2f offset(10.f, 10.f);
            enemy->spawn(mousePosView + offset);
            enemies.push_back(enemy);
            //Prevent mouse holding
            info.mouseButtonPressed = false;
        }

        //Delete enemies
        bool deleted{};
        for (size_t i{}; i < enemies.size() && deleted == false; ++i)
        {
            enemies[i]->move();

            //Delete enemy if we kill it
            if (info.isMouseMoved && enemies[i]->contains(mousePosView))
            {
                //Add points
                int gettedPoints = enemies[i]->getID() * info.strength;
                info.points += gettedPoints;
                //Spawn getted points text
                texts[1]->spawn(mousePosView, std::to_string(gettedPoints));

                deleted = true;
            }

            //Delete enemy if not in window
            if (!enemies[i]->inTargetWindow(window))
                deleted = true;
            
            //Delete enemy
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

    ++info.frameCount;
}