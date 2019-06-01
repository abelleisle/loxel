#include <iostream>
#include <exception>
#include <stdexcept>
#include <functional>
#include <thread>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/asio.hpp>

#include <client/client.hpp>

Client::Client()
{}

Client::~Client()
{}

int Client::init()
{
    // Start GLFW
    if (!glfwInit()) {
        std::cerr << "ERROR: Could not start GLFW" << std::endl;
        return -1;
    }

    render.init();

    return 0;
}

void Client::start()
{
    std::thread renderThread([&](){render.start();});
    std::thread mainThread([&](){this->loop();});

    renderThread.join();
    mainThread.join();
}

void Client::loop()
{
    do {

    } while (glfwGetKey(render.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            !glfwWindowShouldClose(render.getWindow()));

    render.stop();
}

void Client::input()
{}

void Client::graphics()
{}

void Client::cleanup()
{}
