#include <client/client.hpp>
#include <script/script.hpp>
#include <script/script_exception.hpp>
#include <config.hpp>

#include <iostream>
#include <exception>
#include <stdexcept>
#include <functional>
#include <thread>
#include <chrono>

Client::Client()
{
}

Client::~Client()
{
    
}

void Client::init()
{

    const std::string configFile = "config/loxel.conf";

    Configuration clientConfig;
    try {
        clientConfig.loadfile(configFile);
    } catch (ScriptException::FileNotFound &fnf) {
        clientConfig.createfile(configFile);
        clientConfig.loadfile(configFile);
    }

    // Initialize configs and their default values
    clientConfig.addItem("monitor_width", 1280);
    clientConfig.addItem("monitor_height", 720);
    clientConfig.addItem("game_title", std::string("loxel"));

    clientConfig.readConfig();

    double width;
    double height;
    std::string title;

    try {
        width = clientConfig.getItem<double>("monitor_width");
        height = clientConfig.getItem<double>("monitor_height");
        title = clientConfig.getItem<std::string>("game_title");
    } catch (std::exception &oof) {}

    // TODO error handling

    display = Display(title, static_cast<int>(width), static_cast<int>(height));

    graphicsEngine = GraphicsEngine(this);
    // this creates the window
    graphicsEngine.init();

    inputHandler = InputHandler(this);
}

void Client::gameLoop()
{
    while (running) {
        
    }
}

void Client::loop()
{
    gameThread = std::thread(&Client::gameLoop, this);
}

void Client::input()
{
    inputThread = std::thread(&InputHandler::inputLooper, inputHandler);
}

void Client::graphics()
{
    graphicsEngine.drawLoop();
}

void Client::cleanup()
{
    if (gameThread.joinable())
        gameThread.join();
    if (inputThread.joinable())
        inputThread.join();
}

Display* Client::getDisplay()
{
    return &display;
}
