#include <display.hpp>
#include <vec.hpp>

Display::Display(std::string title, int width, int height)
{
    this->title = title;
    this->screenSize = vec2<int>(width, height);
}

Display::Display()
{
    Display("loxel", 1920, 1080);
}
