#ifndef GAME_HPP
#define GAME_HPP

#include <boost/asio.hpp>
#include <thread>

// TODO remove this to make threadpool
#include <thread>

class Game
{
    private:
        virtual void loop() = 0;

    protected:
        float deltaTime;
        unsigned long long cycles;

        std::thread gameThread;
        std::thread inputThread;

        //boost::asio::thread_pool t_pool(std::thread::hardware_concurrency());

    public:
        Game();
        virtual ~Game();

        virtual int init() = 0;
        virtual void start() = 0;
        virtual void input() = 0;
        virtual void graphics() = 0;
        virtual void cleanup() = 0;

        float getDeltaTime();
        float setDeltaTime(float);

        bool isRunning();
        void stopGame();
};

#endif // GAME_HPP

