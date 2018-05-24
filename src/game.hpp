#ifndef GAME_HPP
#define GAME_HPP

#include <thread>

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

        bool running;

        std::thread gameThread;
        std::thread inputThread;
    public:
        Game();
        ~Game();

        virtual void init() = 0;
        virtual void loop() = 0;
        virtual void input() = 0;
        virtual void graphics() = 0;
        virtual void cleanup() = 0;
};

#endif // GAME_HPP
