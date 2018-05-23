#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>

#include <SDL2/SDL.h>

#include <vec.hpp>

class Display
{
    private:
        std::string title;
        vec2<int> screenSize;

        SDL_Window *window;
        SDL_GLContext context;
    public:
        Display();
        Display(std::string, int, int);
       ~Display();

        void create();

        SDL_Window* getWindow();
};

#endif // DISPLAY_HPP
