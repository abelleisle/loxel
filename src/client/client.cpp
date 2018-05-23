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

    Script s;
    try {
        s.loadfile("scripts/load.lua");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
