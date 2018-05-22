#ifndef GAME_HPP
#define GAME_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>

#include <display.hpp>

class Game
{
    private:
        Display display;

        int deltaTime;
    public:
        Game();
        ~Game();

        void init();
};

#endif // GAME_HPP
