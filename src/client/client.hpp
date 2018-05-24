#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <game.hpp>

#include <client/display.hpp>

class Client : public Game
{
    private:
        Display display;

        void gameLoop();
    public:
        Client();
       ~Client();

        void init();
        void loop();
        void input();
        void graphics();
        void cleanup();
};

#endif // CLIENT_HPP
