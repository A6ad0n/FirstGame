#include "Enemy.h"

void Enemy::initID()
{
    this->ID = 1 + rand() % 49;
}

void Enemy::initTextures()
{
    std::string source = "resources/sprites/craftpix-net-354073-free-emoji-icons-for-rpg-games/PNG/without background/";
    source += std::to_string(this->ID) + ".png";
    this->enemyTexture.loadFromFile(source);
}

void Enemy::initVariables()
{
    //enemy
    this->enemy.setPosition(0.0f, 0.0f);
    this->enemy.setTexture(this->enemyTexture);
}

void Enemy::initSpeed()
{
    this->initSpeed(-3,3);
}

void Enemy::initSpeed(const int &a, const int &b)
{
    int range;
    if ((b < 0 && a > 0) || (b > 0 && a < 0) ||
        (b > 0 && a >= 0) || (b <= 0 && a < 0))
        range = 10 * (b - a) + 1;
    else
        range = 10 * (b - a);
    do
    {
        this->speed = sf::Vector2f(
        static_cast<float>(a * 10 + rand() % range) / 10,
        static_cast<float>(a * 10 + rand() % range) / 10
        
    );
    } while (this->speed.x == 0.0f || this->speed.y == 0.0f);
}

void Enemy::initScale()
{
    this->scale = sf::Vector2f(0.15f, 0.15f);
}

void Enemy::initCost()
{
    this->cost = this->ID;
}

Enemy::Enemy()
{
    initID();
    initTextures();
    initVariables();
    initSpeed();
    initScale();
    initCost();
}

Enemy::~Enemy()
{

}

void Enemy::setPosition(const sf::Vector2f &position)
{
    this->enemy.setPosition(
        position.x,
        position.y
    );
}

void Enemy::setScale(const sf::Vector2f &factors)
{
    this->enemy.setScale(
        factors.x,
        factors.y
    );
}

int Enemy::getID()
{
    return this->ID;
}

sf::Vector2f Enemy::getSize()
{
    return this->enemy.getGlobalBounds().getSize();
}

sf::Vector2f Enemy::getPosition()
{
    return this->enemy.getPosition();
}

void Enemy::spawn(const sf::VideoMode &videomode)
{
    this->enemy.setPosition(sf::Vector2f(
        static_cast<float>(rand() % static_cast<int>(videomode.width)),
        static_cast<float>(rand() % static_cast<int>(videomode.height))
    ));
    this->enemy.setScale(this->scale);
}

void Enemy::spawn(const float &x, const float &y)
{
    this->enemy.setPosition(x, y);
    this->enemy.setScale(this->scale);
}

void Enemy::spawn(const sf::Vector2f &position)
{
    this->enemy.setPosition(position.x, position.y);
    this->enemy.setScale(this->scale);
}

void Enemy::move()
{
    this->enemy.move(
        this->speed.x,
        this->speed.y
    );
}

bool Enemy::contains(const sf::Vector2f &point)
{
    return this->enemy.getGlobalBounds().contains(
        point.x,
        point.y
    );
}

bool Enemy::inTargetWindow(sf::RenderTarget* target)
{
    return  this->enemy.getPosition().y > target->getSize().y ||
            this->enemy.getPosition().y < - (this->enemy.getGlobalBounds().getSize().y) ||
            this->enemy.getPosition().x > target->getSize().x ||
            this->enemy.getPosition().x < - (this->enemy.getGlobalBounds().getSize().x);
}

void Enemy::render(sf::RenderTarget* target)
{
    target->draw(this->enemy);
}