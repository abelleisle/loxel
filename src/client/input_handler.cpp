#include <client/input_handler.hpp>
#include <client/camera.hpp>
#include <client/graphics_engine.hpp>

InputHandler::InputHandler()
{}

InputHandler::~InputHandler()
{
}

void InputHandler::inputLooper()
{
    while (GameState::isRunning()) {
        static SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch(e.type) {
            case SDL_QUIT:
                GameState::stopGame();
                break;
            default: break;
            }
        }
    }
}

void InputHandler::windowEvents()
{

}
