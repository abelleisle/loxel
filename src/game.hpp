#ifndef GAME_HPP
#define GAME_HPP

#include <thread>

class Game
{
    private:
    protected:
        int deltaTime;
        unsigned long long cycles;

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
};

#endif // GAME_HPP
