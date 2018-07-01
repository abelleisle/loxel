#include <game_class.hpp>
#include <script/script.hpp>
#include <script/script_exception.hpp>

namespace GameState
{
    Configuration clientConfig;
    bool __game_running = true;

    void createConfig()
    {
        const std::string configFile = "config/loxel.conf";

        try {
            clientConfig.loadfile(configFile);
        } catch (ScriptException::FileNotFound &fnf) {
            clientConfig.createfile(configFile);
            clientConfig.loadfile(configFile);
        }
    }

    void readConfig()
    {

        clientConfig.readConfig();
    }

    void stopGame()
    {
        __game_running = false;
    }

    bool isRunning()
    {
        return __game_running;
    }
}
