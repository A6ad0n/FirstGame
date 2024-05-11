#include "Game.h"

void Game::initVariables()
{
    gameCondition = true;

    window = nullptr;

    info.enemySpawnerTimer = 0;
    info.points = 50;
    info.strength = 1;
    info.costStrength = 500;
    info.efficiency = 1;
    info.costEfficiency = 2000;

    info.isMouseMoved = false;
    info.mouseButtonPressed = false;
    info.mouseOnTarget = false;
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
        font, 0, 30, sf::Color::White   //GUI text
    ));
    texts.push_back(new Text(
        font, 1, 50, sf::Color::Red     //Getted points text
    ));
    texts.push_back(new Text(
        font, 2, 100, sf::Color::Black  //Upgrade text
    ));
    texts.push_back(new Text(           //Lose text
        font, 3, 60, sf::Color::Magenta
    ));
}

void Game::initGUIText()
{
    bgGUIText.setFillColor(sf::Color(0, 0, 0, 160));
    bgGUIText.setPosition(80.f, 0.f);
    bgGUIText.setSize(sf::Vector2f(500.f, 300.f));
    texts[0]->spawn(sf::Vector2f(90.f, 10.f), "");
}

void Game::initBackground()
{
    bgTexture.loadFromFile("resources/sprites/photo_2024-05-11 21.30.16.jpeg");
    background.setTexture(bgTexture);
    sf::FloatRect bounds = background.getLocalBounds();
    background.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    background.setPosition(window->getView().getCenter());
}

void Game::initTargets()
{
    target1.setFillColor(sf::Color::White);
    target2.setFillColor(sf::Color::White);
    target1.setRadius(50.f);
    target2.setRadius(50.f);
    sf::FloatRect bounds1 = target1.getLocalBounds();
    sf::FloatRect bounds2 = target2.getLocalBounds();
    target1.setOrigin(bounds1.left + bounds1.width / 2.f, bounds1.top + bounds1.height / 2.f);
    target2.setOrigin(bounds2.left + bounds2.width / 2.f, bounds2.top + bounds2.height / 2.f);
    target1.setPosition(990.f, 510.f);
    target2.setPosition(530.f, 510.f);
}

void Game::initSounds()
{
    buffer.loadFromFile("resources/sounds/pop.wav");
    sound.setBuffer(buffer);
}

Game::Game()
{
    initVariables();
    initWindow();
    initText();
    initGUIText();
    initBackground();
    initTargets();
    initSounds();
}

Game::~Game()
{
    delete window;
    
    for (size_t i{}; i < texts.size(); ++i)
        delete texts[i];
}

void Game::playMusic()
{
    music.openFromFile("resources/sounds/music.wav");
    music.setLoop(true);
    music.play();
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
                                texts[2]->spawn(window->getView().getCenter(), "Upgrade Strength!");
                            }
                            else
                                texts[2]->spawn(window->getView().getCenter(), "Not enough points");
                            break;
                        case sf::Keyboard::Down:
                            if (info.points >= info.costEfficiency)
                            {
                                if (info.efficiency < 5)
                                {
                                    info.efficiency += 1;
                                    info.points -= info.costEfficiency;
                                    info.costEfficiency *= 4;
                                    sf::Vector2f offset(250.f, 250.f);
                                    texts[2]->spawn(window->getView().getCenter(), "Upgrade Efficiency!");
                                }
                                else
                                    texts[2]->spawn(window->getView().getCenter(), "Max level of efficiency");
                            }
                            else
                                texts[2]->spawn(window->getView().getCenter(), "Not enough points");
                            break;
                        //Debug mode switch
                        case sf::Keyboard::Enter:
                            info.isDebug = !info.isDebug;
                        default:
                            break;
                    }
                
                case sf::Event::MouseMoved:
                {
                    if (info.mousePosView.y < 560.f && info.mousePosView.y > 460.f && 
                    ((info.mousePosView.x < 1040.f && info.mousePosView.x > 940.f) || 
                    (info.mousePosView.x < 580.f && info.mousePosView.x > 480.f)))
                        info.mouseOnTarget = true;
                    else
                        info.mouseOnTarget = false;

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
        info.mousePosView = window->mapPixelToCoords(mousePosWindow);
    }

    //Update enemies
    {
        if (info.mouseOnTarget && info.mouseButtonPressed && enemies.size() < Consts::maxEnemies && gameCondition)
        {
            size_t availableAmount = Consts::maxEnemies - enemies.size();
            for (size_t i{}; i < availableAmount && i < info.efficiency; ++i)
            {
                Enemy* enemy = new Enemy();
                sf::Vector2f offset(10.f, 10.f);
                enemy->spawn(info.mousePosView + offset);
                enemies.push_back(enemy);
            }
            //Prevent mouse holding
            info.mouseButtonPressed = false;
        }

        //Delete enemies
        bool deleted{};
        for (size_t i{}; i < enemies.size() && deleted == false; ++i)
        {
            enemies[i]->move();

            //Delete enemy if we kill it
            if (info.isMouseMoved && enemies[i]->contains(info.mousePosView))
            {
                //Add points
                int gettedPoints = enemies[i]->getID() * info.strength;
                info.points += gettedPoints;
                //Spawn getted points text
                texts[1]->spawn(info.mousePosView, std::to_string(gettedPoints));

                deleted = true;
            }

            //Delete enemy if not in window
            if (!enemies[i]->inTargetWindow(window))
            {
                if (info.points < enemies[i]->getID() * info.strength)
                    gameCondition = false;
                else
                    info.points -= enemies[i]->getID() * info.strength;
                deleted = true;
            }
            
            //Delete enemy
            if (deleted)
                {
                    sound.play();
                    delete enemies[i];
                    enemies.erase(enemies.begin() + i);
                    deleted = false;
                }
        }
    }

    //Update game condition
    {
        if (!gameCondition)
            texts[3]->spawn(window->getView().getCenter(), "You've lost this game!");
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

    //render background
    {
        window->draw(background);
        window->draw(bgGUIText);
    }

    //render Targets
    {
        window->draw(target1);
        window->draw(target2);
    }

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