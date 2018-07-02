#ifndef GAME_HPP
#define GAME_HPP

#include <thread>

class GraphicsEngine;

class Game
{
    private:
    protected:
        float deltaTime;
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

        float getDeltaTime();
        float setDeltaTime(float);

        bool isRunning();
        void stopGame();

        virtual GraphicsEngine* getGraphicsEngine() {return nullptr;}
};

#endif // GAME_HPP
