#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <game.hpp>

#include <client/RenderSystem.hpp>

class Client : public Game
{
    private:
        void gameLoop();
        RenderSystem render;

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
