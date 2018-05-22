#include <game.hpp>

Game::Game()
{
    deltaTime = 0;
}

Game::~Game()
{

}

void Game::init()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
}
