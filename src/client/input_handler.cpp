#include <client/input_handler.hpp>
#include <client/camera.hpp>
#include <client/graphics_engine.hpp>

#include <iostream>
#include <chrono>
#include <thread>

InputHandler::InputHandler()
{}

InputHandler::~InputHandler()
{}

void InputHandler::inputLooper()
{
    while (GameState::isRunning()) {
        static SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch(e.type) {
            case SDL_QUIT:
                GameState::stopGame();
                break;
            case SDL_MOUSEMOTION:
                static const float mouseSpeed = 0.001;
                GameState::gameObject()->getGraphicsEngine()->getCamera()->angle.x
                    -= e.motion.xrel * mouseSpeed;

                GameState::gameObject()->getGraphicsEngine()->getCamera()->angle.y
                    -= e.motion.yrel * mouseSpeed;

                break;
            case SDL_KEYUP:
                switch(e.key.keysym.sym) {
                case SDLK_w:
                    GameState::gameObject()->getGraphicsEngine()->getCamera()->w_f = false;
                    break;
                case SDLK_s:
                    GameState::gameObject()->getGraphicsEngine()->getCamera()->w_b = false;
                    break;
                case SDLK_a:
                    GameState::gameObject()->getGraphicsEngine()->getCamera()->w_l = false;
                    break;
                case SDLK_d:
                    GameState::gameObject()->getGraphicsEngine()->getCamera()->w_r = false;
                    break;
                }
                break;
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym) {
                case SDLK_w:
                    GameState::gameObject()->getGraphicsEngine()->getCamera()->w_f = true;    
                    break;
                case SDLK_s:
                    GameState::gameObject()->getGraphicsEngine()->getCamera()->w_b = true;
                    break;
                case SDLK_a:
                    GameState::gameObject()->getGraphicsEngine()->getCamera()->w_l = true;
                    break;
                case SDLK_d:
                    GameState::gameObject()->getGraphicsEngine()->getCamera()->w_r = true;
                    break;
                }
                break;
            default: break;
            }
        }
    }
}

void InputHandler::windowEvents()
{

}
