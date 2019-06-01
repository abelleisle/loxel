#ifndef SERVER_HPP
#define SERVER_HPP

#include <game.hpp>

class Server : public Game
{
    private:

        void loop();

    public:
        Server();
        virtual ~Server();

        int init();
        void start();
        void input();
        void graphics();
        void cleanup();
};

#endif // SERVER_HPP
