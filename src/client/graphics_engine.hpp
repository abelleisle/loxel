#ifndef GRAPHICS_ENGINE_HPP
#define GRAPHICS_ENGINE_HPP

#include <SDL2/SDL.h>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>

#include <game.hpp>
#include <client/shader.hpp>
#include <client/camera.hpp>

class GraphicsEngine
{
    private:
        SDL_GLContext context;
        SDL_Window* window;

        Game* client;
        Camera cam;
        std::unordered_map<std::string, Shader> shaders;
    public:
        GraphicsEngine();
        GraphicsEngine(Game*);
       ~GraphicsEngine();

        Camera* getCamera();
    
        int init();
        int drawLoop();

        void addShader(std::string, Shader);
};

#endif // GRAPHICS_ENGINE_HPP
