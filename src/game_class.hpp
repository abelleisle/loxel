#ifndef GAME_CLASS_HPP
#define GAME_CLASS_HPP

#include <game.hpp>
#include <config.hpp>

namespace GameState
{
    extern Configuration clientConfig;

    void createConfig();
    void readConfig();
    void stopGame();
    bool isRunning();

    void setGameObject(Game*);
    Game* gameObject();

    void cleanup();
}
#endif //GAME_CLASS_HPP
