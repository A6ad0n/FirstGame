#pragma once

struct GameInfo
{
    unsigned int enemySpawnerTimer;
    int points;
    int strength;
    int costStrength;

    bool isMouseMoved;
    bool mouseButtonPressed;
    bool isDebug;
    int frameCount;
};