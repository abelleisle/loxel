
#include <client/display.hpp>
#include <vec.hpp>

Display::Display(std::string title, int width, int height)
{
    this->title = title;
    this->screenSize = vec2<int>(width, height);

    SDL_Init(SDL_INIT_VIDEO);

    // Select an OpenGL 2.1 profile.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    window = nullptr;
    context = nullptr;
}

Display::Display()
{
    Display("loxel", 1920, 1080);
}

void Display::create()
{
    window = SDL_CreateWindow(title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenSize.x, screenSize.y,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    context = SDL_GL_CreateContext(window);
}

SDL_Window* Display::getWindow()
{
    return window;
}

Display::~Display()
{
    if (context != nullptr)
        SDL_GL_DeleteContext(context);
    if (window != nullptr)
        SDL_DestroyWindow(window);

    SDL_Quit();
}
