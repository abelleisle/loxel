#include <client/client.hpp>
#include <script/script.hpp>
#include <script/script_exception.hpp>
#include <config.hpp>

#include <iostream>
#include <exception>
#include <stdexcept>

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

    clientConfig.readConfig();
    
    try {
        std::cout << std::experimental::any_cast<double>(
                clientConfig.getItem("monitor_width")
        ) << std::endl;
    } catch (std::exception &oof) {}

    try {
        std::cout << std::experimental::any_cast<double>(
                clientConfig.getItem("monitor_height")
        ) << std::endl;
    } catch (std::exception &oof) {}



    display = Display("loxel", 1920, 1080);
    display.create();
}
