#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <game.hpp>

class Client : public Game
{
    private:
        void gameLoop();
    public:
        Client();
        virtual ~Client();

        int init();
        void loop();
        void input();
        void graphics();
        void cleanup();
};

#endif // CLIENT_HPP
