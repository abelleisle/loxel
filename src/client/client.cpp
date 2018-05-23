#include <client/client.hpp>
#include <script/script.hpp>

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
    display = Display("loxel", 1920, 1080);
    display.create();

    Script config;
    try {
        config.loadfile("config/loxel.conf");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
