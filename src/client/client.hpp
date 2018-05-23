#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <game.hpp>

#include <client/display.hpp>

class Client : public Game
{
    private:
        Display display;
    public:
        Client();
       ~Client();

        void init();
};

#endif // CLIENT_HPP
