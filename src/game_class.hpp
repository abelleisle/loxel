#ifndef GAME_CLASS_HPP
#define GAME_CLASS_HPP

#include <game.hpp>
#include <config.hpp>
#include <script/script.hpp>
#include <script/script_exception.hpp>

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

    Script* getGlobalScript();
}
#endif //GAME_CLASS_HPP
