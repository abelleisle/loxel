#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>

#include <glm/glm.hpp>

#include <vec.hpp>

class Display
{
    private:
        std::string title;
        vec2<int> screenSize;
    public:
        Display(std::string, int, int);
};

#endif // DISPLAY_HPP
