#include <config.hpp>
#include <iostream>
#include <fstream>
#include <typeinfo>

Configuration::Configuration()
{
    rewriteFile = false;
}

Configuration::~Configuration()
{
    if(rewriteFile)
        writeConfig();
}

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
    unsigned int found = 0;
    for (auto it : configItems) {
        found++;
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
            found--;
            break;
        }
    }

    if (found < configItems.size())
        rewriteFile = true;
}

void Configuration::createfile(std::string filename)
{
    std::fstream file;
    file.open(filename, std::fstream::out);
}

void Configuration::writeConfig()
{
    std::fstream file;
    file.open(configFile, std::fstream::out);

    // go through every item and try casting it as every possible type of
    // lua variable
    //      yeah... this is gross. pretend you don't see it.
    for (auto it : configItems) {
        try {
            std::string s_value = std::experimental::any_cast<std::string>(it.second);
            file << it.first << " = \"" << s_value << "\"" << std::endl;
        } catch (std::experimental::bad_any_cast &s_bac) {
            try {
                double d_value = std::experimental::any_cast<double>(it.second);
                file << it.first << " = " << d_value << std::endl;
            } catch (std::experimental::bad_any_cast &d_bac) {
                try {
                    bool b_value = std::experimental::any_cast<bool>(it.second);
                    file << it.first << " = " << b_value << std::endl;
                } catch (std::experimental::bad_any_cast &b_bac) {
                    try {
                        int i_value = std::experimental::any_cast<int>(it.second);
                        file << it.first << " = " << i_value << std::endl;
                    } catch (std::experimental::bad_any_cast &i_bac) {
                        file << it.first << " = nil" << std::endl;
                    }
                }
            }
        }
    }

    file.close();
}
