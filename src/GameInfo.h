#pragma once

struct GameInfo
{
    unsigned int enemySpawnerTimer;
    unsigned int points;
    unsigned int strength;
    unsigned int costStrength;
    unsigned int efficiency;
    unsigned int costEfficiency;

    sf::Vector2f mousePosView;
    bool isMouseMoved;
    bool mouseButtonPressed;
    bool mouseOnTarget;
    bool isDebug;
    unsigned int frameCount;
};