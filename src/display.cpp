#include <display.hpp>
#include <vec.hpp>

Display::Display(std::string title, int width, int height):
    title(title), screenSize(vec2<int>(width, height))
{
}
