#include "Game.h"

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    Game game;

    game.playMusic();

    while (game.isRunning())
    {
        game.update();
        game.render();
    }
    
    return 0;
}