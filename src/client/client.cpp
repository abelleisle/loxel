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

#include <config/config.hpp>
#include <script/script.hpp>

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
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_loadfile(L, "config/config.lua") || lua_pcall(L, 0, 0, 0)) {
        std::cout << "File not found" << std::endl;
    }

    LuaRef v = getGlobal(L, "game");
    LuaRef n = getGlobal(L, "value");
    //lua_getglobal(L, "game");
    //Script::print_table(L);
    //LuaRef a = getGlobal(L, "value");
    std::cout << Script::printValue("game", v) << std::endl;
    std::cout << Script::printValue("value", n) << std::endl;

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
