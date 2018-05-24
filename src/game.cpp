#include <game.hpp>

Game::Game()
{
    deltaTime = 0;
    cycles = 0;

    running = true;

    gameThread = std::thread();
    inputThread = std::thread();
}

Game::~Game()
{

}
