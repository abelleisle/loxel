#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <unordered_map>
#include <variant>
#include <fstream>

#include <lua/lua.hpp>
#include <LuaBridge/LuaBridge.h>

using namespace luabridge;

using Lua_T = std::variant<std::string, bool, double>;

class ConfigOption
{
    private:
        std::string key;
        Lua_T value;
    public:
        ConfigOption(std::string, Lua_T value);

        Lua_T getValue();
        Lua_T setValue(Lua_T);

        void print(std::fstream);
};

class ConfigTable
{
    private:
        std::unordered_map<std::string, ConfigOption> entries;
        std::unordered_map<std::string, ConfigTable*> sections;
    public:
        ConfigTable();

        ConfigOption getEntry(std::string);
        ConfigTable getSection(std::string);

        ConfigTable addSection(std::string);
        ConfigTable addEntry(std::string, Lua_T);

        void print(std::fstream);
};

class Configuration
{
    private:
        std::string name;
        std::string file;
        ConfigTable table;
    public:
        void read();
        void write();
        void update();

        ConfigTable getConfig();
};

#endif // CONFIG_HPP
