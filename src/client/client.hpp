#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <game.hpp>

#include <client/display.hpp>
#include <client/input_handler.hpp>

class Client : public Game
{
    private:
        Display display;
        InputHandler inputHandler;

        void gameLoop();
    public:
        Client();
        virtual ~Client();

        void init();
        void loop();
        void input();
        void graphics();
        void cleanup();
};

#endif // CLIENT_HPP
