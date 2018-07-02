#include <game.hpp>
#include <game_class.hpp>

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
    return GameState::isRunning();
}

void Game::stopGame()
{
    GameState::stopGame();
}

float Game::getDeltaTime()
{
    return deltaTime;
}

float Game::setDeltaTime(float dt)
{
    deltaTime = dt;
    return dt;
}
