#include <config/config.hpp>


ConfigOption::ConfigOption(std::string key, Lua_T value)
    : key(key), value(value)
{}

Lua_T ConfigOption::getValue()
{
    return value;
}

Lua_T ConfigOption::setValue(Lua_T value)
{
    return value;
}

void ConfigOption::print(std::fstream file)
{
    file << "hih";
}
