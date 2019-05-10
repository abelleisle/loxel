#include <game.hpp>

Game::Game()
{
    deltaTime = 0;
    cycles = 0;
}

Game::~Game()
{

}

bool Game::isRunning()
{
    return true;
}

void Game::stopGame()
{}

float Game::getDeltaTime()
{
    return deltaTime;
}

float Game::setDeltaTime(float dt)
{
    deltaTime = dt;
    return dt;
}
