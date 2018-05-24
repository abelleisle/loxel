#include <game.hpp>

Game::Game()
{
    deltaTime = 0;
    cycles = 0;

    running = true;
}

Game::~Game()
{

}

bool Game::isRunning()
{
    return running;
}

void Game::stopGame()
{
    running = false;
}
