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

    boost::asio::thread_pool t_pool(
        std::thread::hardware_concurrency()
    );

    boost::asio::post(t_pool, [&](){render.start();});

    render.stop();
    t_pool.join();

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
}
