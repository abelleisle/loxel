#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SDL2/SDL.h>

#include <game_class.hpp>

class InputHandler
{
    private:
    public:
        InputHandler();
       ~InputHandler();

        void inputLooper();
        void windowEvents();
};

#endif // INPUT_HANDLER_HPP
