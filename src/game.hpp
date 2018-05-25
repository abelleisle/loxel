#ifndef GAME_HPP
#define GAME_HPP

#include <thread>

#include <client/display.hpp>

class Game
{
    private:
    protected:
        int deltaTime;
        unsigned long long cycles;

        bool running;

        std::thread gameThread;
        std::thread inputThread;
    public:
        Game();
        virtual ~Game();

        virtual void init() = 0;
        virtual void loop() = 0;
        virtual void input() = 0;
        virtual void graphics() = 0;
        virtual void cleanup() = 0;

        bool isRunning();
        void stopGame();

        virtual Display* getDisplay(){return NULL;}
};

#endif // GAME_HPP
