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
            std::vector<int> primes;
            for (int i = 3; i < 10000000 && GameState::isRunning(); i += 2) {
                bool prime = true;
                for (int n = 3; n < i; n += 2) {
                    if (i % n == 0) {
                        prime = false;
                        break;
                    }
                }
                if (prime) {
                    primes.push_back(i);
                    std::cout << i << " is prime!" << std::endl;
                }
            }
            std::cout << "Done!" << std::endl;
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
