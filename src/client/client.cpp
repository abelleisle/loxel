#include <client/client.hpp>
#include <config.hpp>

#include <iostream>
#include <exception>
#include <stdexcept>
#include <functional>
#include <thread>
#include <chrono>

Client::Client()
{
}

Client::~Client()
{
}

void Client::init()
{
    GameState::setGameObject(this);
    GameState::createConfig();

    graphicsEngine = GraphicsEngine();
    inputHandler = InputHandler();

    GameState::readConfig();

    // this creates the window
    graphicsEngine.init();
}

void Client::gameLoop()
{
    float accum = 0.0;
    while (GameState::isRunning()) {
        accum += deltaTime;
        if (accum >= 50) {
            accum = 0;
        } else {
            SDL_Delay(deltaTime);
        }
    }
}

void Client::loop()
{
    gameThread = std::thread(&Client::gameLoop, this);
}

void Client::input()
{
    inputThread = std::thread(&InputHandler::inputLooper, inputHandler);
}

void Client::graphics()
{
    graphicsEngine.drawLoop();
}

void Client::cleanup()
{
    if (gameThread.joinable())
        gameThread.join();
    if (inputThread.joinable())
        inputThread.join();
    GameState::cleanup();
}
