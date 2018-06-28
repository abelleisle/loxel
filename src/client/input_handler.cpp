#include <client/input_handler.hpp>
#include <client/camera.hpp>
#include <client/graphics_engine.hpp>

InputHandler::InputHandler()
{}

InputHandler::InputHandler(Game* client)
    : client(client)
{}

InputHandler::~InputHandler()
{
    client = NULL;
}

void InputHandler::inputLooper()
{
    while (client->isRunning()) {
        static SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch(e.type) {
            case SDL_QUIT:
                client->stopGame();
                break;
            default: break;
            }
        }
    }
}

void InputHandler::windowEvents()
{

}
