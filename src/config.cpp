#include <config.hpp>
#include <iostream>
#include <fstream>

Configuration::Configuration()
{}

Configuration::~Configuration()
{}

void Configuration::loadfile(std::string configFile)
{
    this->configFile = configFile;
    script.loadfile(configFile);
}

bool Configuration::addItem(std::string key, std::experimental::any value)
{
    auto it = configItems.find(key);
    if (it != configItems.end())
        it->second = value;
    else
        configItems.emplace(key, value);

    return true;
}

bool Configuration::addItem(std::string key)
{
    auto it = configItems.find(key);
    if (it != configItems.end())
        it->second = 0;
    else
        configItems.emplace(key, 0);

    return true;
}

bool Configuration::setItem(std::string key, std::experimental::any value)
{
    return addItem(key, value);
}

std::experimental::any Configuration::getItem(std::string key)
{
    return configItems.at(key);
}

void Configuration::readConfig()
{
    for (auto it : configItems) {
        lua_getglobal(script.getState(), it.first.c_str());
        switch (lua_type(script.getState(), -1)) {
        case LUA_TSTRING:
            setItem(it.first, lua_tostring(script.getState(), -1));
            break;
        case LUA_TBOOLEAN:
            setItem(it.first, lua_toboolean(script.getState(), -1));
            break;
        case LUA_TNUMBER:
            setItem(it.first, lua_tonumber(script.getState(), -1));
            break;
        default:
            break;
        }
    }
}

void Configuration::createfile(std::string filename)
{
    std::fstream file;
    file.open(filename, std::fstream::out);
}
