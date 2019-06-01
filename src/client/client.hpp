#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <game.hpp>

#include <client/RenderSystem.hpp>

class Client : public Game
{
    private:
        RenderSystem render;

        void loop();

    public:
        Client();
        virtual ~Client();

        int init();
        void start();
        void input();
        void graphics();
        void cleanup();
};

#endif // CLIENT_HPP
