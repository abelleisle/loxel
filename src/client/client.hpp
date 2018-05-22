#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <game.hpp>

class Client : public Game
{
    private:
    public:
        Client();
        ~Client();

        void init();
};

#endif // CLIENT_HPP
