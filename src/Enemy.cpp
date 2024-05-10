#include "Enemy.h"

void Enemy::initID()
{
    ID = 1 + rand() % 49;
}

void Enemy::initTextures()
{
    std::string source = "resources/sprites/craftpix-net-354073-free-emoji-icons-for-rpg-games/PNG/without background/";
    source += std::to_string(ID) + ".png";
    enemyTexture.loadFromFile(source);
}

void Enemy::initVariables()
{
    enemy.setPosition(0.0f, 0.0f);
    enemy.setTexture(enemyTexture);
    scale = sf::Vector2f(0.15f, 0.15f);
    cost = ID;
}

void Enemy::initSpeed()
{
    initSpeed(-3,3);
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
        speed = sf::Vector2f(
        static_cast<float>(a * 10 + rand() % range) / 10,
        static_cast<float>(a * 10 + rand() % range) / 10
        
    );
    } while (speed.x == 0.0f || speed.y == 0.0f);
}

Enemy::Enemy()
{
    initID();
    initTextures();
    initVariables();
    initSpeed();
}

Enemy::~Enemy()
{

}

void Enemy::setScale(const sf::Vector2f &factors)
{
    enemy.setScale(
        factors.x,
        factors.y
    );
}

int Enemy::getID() const
{
    return ID;
}

void Enemy::spawn(const sf::VideoMode &videomode)
{
    enemy.setPosition(sf::Vector2f(
        static_cast<float>(rand() % static_cast<int>(videomode.width)),
        static_cast<float>(rand() % static_cast<int>(videomode.height))
    ));
    enemy.setScale(scale);
}

void Enemy::spawn(const float &x, const float &y)
{
    enemy.setPosition(x, y);
    enemy.setScale(scale);
}

void Enemy::spawn(const sf::Vector2f &position)
{
    enemy.setPosition(position.x, position.y);
    enemy.setScale(scale);
}

void Enemy::move()
{
    enemy.move(
        speed.x,
        speed.y
    );
}

bool Enemy::contains(const sf::Vector2f &point) const
{
    return enemy.getGlobalBounds().contains(
        point.x,
        point.y
    );
}

bool Enemy::contains(const float &x, const float &y) const
{
    return enemy.getGlobalBounds().contains(x, y);
}

bool Enemy::inTargetWindow(sf::RenderTarget* target) const
{
    return  !(enemy.getPosition().y > target->getSize().y ||
            enemy.getPosition().y < - (enemy.getGlobalBounds().getSize().y) ||
            enemy.getPosition().x > target->getSize().x ||
            enemy.getPosition().x < - (enemy.getGlobalBounds().getSize().x));
}

void Enemy::render(sf::RenderTarget* target) const
{
    target->draw(enemy);
}