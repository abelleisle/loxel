#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SDL2/SDL.h>

#include <game.hpp>

class InputHandler
{
    private:
        Game* client;
    public:
        InputHandler();
        InputHandler(Game*);
       ~InputHandler();

        void inputLooper();
        void windowEvents();
};

#endif // INPUT_HANDLER_HPP
