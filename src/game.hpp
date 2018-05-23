#ifndef GAME_HPP
#define GAME_HPP

#define GLEW_STATIC
#include <GL/glew.h>


#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>

class Game
{
    private:
    protected:
        int deltaTime;
        unsigned long long cycles;
    public:
        Game();
        ~Game();

        virtual void init() = 0;
};

#endif // GAME_HPP
