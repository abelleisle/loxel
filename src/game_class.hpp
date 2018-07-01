#ifndef GAME_CLASS_HPP
#define GAME_CLASS_HPP

#include <config.hpp>

namespace GameState
{
    extern Configuration clientConfig;

    void createConfig();
    void readConfig();
    void stopGame();
    bool isRunning();
}
#endif //GAME_CLASS_HPP
