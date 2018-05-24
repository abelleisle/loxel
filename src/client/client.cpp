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

    double width;
    double height;

    try {
        width = clientConfig.getItem<double>("monitor_width");
        height = clientConfig.getItem<double>("monitor_height");
    } catch (std::exception &oof) {}

    display = Display("loxel", static_cast<int>(width), static_cast<int>(height));
    display.create();
}
