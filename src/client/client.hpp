#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <game.hpp>

#include <client/display.hpp>
#include <client/input_handler.hpp>
#include <client/graphics_engine.hpp>
#include <client/shader.hpp>

class Client : public Game
{
    private:
        Display display;
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

        Display* getDisplay();
};

#endif // CLIENT_HPP
