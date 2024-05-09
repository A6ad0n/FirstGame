#include "Game.h"

void Game::initVariables()
{
    this->window = nullptr;

    this->enemySpawnerTimer = 0;
    this->points = 0;
    this->strength = 1;
    this->costStrength = 500;
    this->isMouseMoved = false;
    this->mouseButtonPressed = false;
    this->isDebug = false;
    this->frameCount = 0;

    this->font.loadFromFile("resources/fonts/Dudka Regular.ttf");
}

void Game::initWindow()
{
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

void Game::initText()
{
    this->Text->setFont(this->font);
    this->Text->setCharacterSize(100);
    this->Text->setFillColor(sf::Color::Red);
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
    this->enemy->spawn(this->mousePosView + sf::Vector2f(10.f, 10.f));
    this->enemies.push_back(this->enemy);
}

void Game::spawnText(const sf::Vector2f &position, const std::string &text)
{
    this->Text = new sf::Text();
    this->initText();
    this->Text->setPosition(
        position.x,
        position.y
    );
    this->Text->setString(text);

    sf::FloatRect textBounds = this->Text->getLocalBounds();
    this->Text->setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    this->gettedPointsTexts.push_back(this->Text);
}

void Game::spawnUpgradeText()
{
    int x = this->videoMode.width / 4;
    int y = this->videoMode.height / 4;
    std::string UpgradeText = "Upgrade!";
    spawnText(sf::Vector2f(x, y), UpgradeText);
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
                    
                    case sf::Keyboard::Up:
                        if (this->points <= this->costStrength)
                        {
                            this->strength += 1;
                            this->points -= this->costStrength;
                            this->costStrength *= 3;
                            this->spawnUpgradeText();
                        }
                        break;
                    
                    case sf::Keyboard::Enter:
                        this->isDebug = !this->isDebug;
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

            case sf::Event::MouseButtonPressed:
                this->mouseButtonPressed = true;
                break;
            
            case sf::Event::MouseButtonReleased:
                this->mouseButtonPressed = false;
                break;
            
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
    if (mouseButtonPressed && this->enemies.size() < Consts::maxEnemies)
    {
        if (this->enemySpawnerTimer >= Consts::enemySpawnerTimerMax)
        {
            this->spawnEnemy();
            this->mouseButtonPressed = false;
            this->enemySpawnerTimer = 0.f;
        }
        else
            this->enemySpawnerTimer += 1.f;
    }

    //move
    bool deleted{};
    for (size_t i{}; i < this->enemies.size() && deleted == false; ++i)
    {
        this->enemies[i]->move();

        if (this->isMouseMoved && this->enemies[i]->contains(this->mousePosView))
        {
            deleted = true;
            this->points += enemies[i]->getID() * this->strength;
            this->spawnText(mousePosView, std::to_string(enemies[i]->getID() * this->strength));
        }

        if (enemies[i]->inTargetWindow(this->window))
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
    std::string output = "Points: " + std::to_string(this->points) + 
    "\nStrength: " + std::to_string(this->strength) +
    "\nUpgrade strength costs: " + std::to_string(this->costStrength);
    if (this->isDebug)
        output += "\nx: " + std::to_string(this->mousePosWindow.x) + 
    " y: " + std::to_string(this->mousePosWindow.y) +
    "\nx: " + std::to_string(static_cast<int>(this->mousePosView.x)) +
    " y: " + std::to_string(static_cast<int>(this->mousePosView.y)) +
    "\nFrame: " + std::to_string(this->frameCount / 60);

    this->pointsText.setString(output);
}

void Game::updateText()
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

    this->updateText();
}

void Game::renderEnemies()
{
    for (auto &e : enemies)
        e->render(this->window);
}

void Game::renderPointsText()
{
    this->window->draw(this->pointsText);
}

void Game::renderText()
{
    for (auto t : gettedPointsTexts)
        this->window->draw(*t);
}

void Game::render()
{
    this->window->clear(sf::Color::Cyan);

    this->renderEnemies();

    this->renderPointsText();

    this->renderText();

    this->window->display();

    ++this->frameCount;
}