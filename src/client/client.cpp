#include <iostream>
#include <exception>
#include <stdexcept>
#include <functional>
#include <thread>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <client/client.hpp>

Client::Client()
{}

Client::~Client()
{}

int Client::init()
{
    if (!glfwInit()) {
        std::cerr << "ERROR: Could not start GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        std::cerr << "ERROR: Could not open GLFW window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "Render: " << renderer;
    std::cout << "OpenGL version supported " << version;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}

void Client::gameLoop()
{}

void Client::loop()
{
    //gameThread = std::thread(&Client::gameLoop, this);
}

void Client::input()
{}

void Client::graphics()
{}

void Client::cleanup()
{
    glfwTerminate();
}
