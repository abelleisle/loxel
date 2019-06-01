#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class RenderSystem
{
    private:
        bool running;
        GLFWwindow* window;
    public:
        RenderSystem();
        ~RenderSystem();

        int init();
        int start();
        void stop();
        void loop();

        GLFWwindow* getWindow();
};

#endif // RENDERSYSTEM_HPP
