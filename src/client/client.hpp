#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <game.hpp>

#include <client/input_handler.hpp>
#include <client/graphics_engine.hpp>
#include <client/shader.hpp>
#include <client/camera.hpp>

class Client : public Game
{
    private:
        GraphicsEngine graphicsEngine;
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
