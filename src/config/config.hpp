#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <unordered_map>
#include <variant>
#include <fstream>
#include <sstream>

#include <lua/lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <script/script.hpp>

using namespace luabridge;
using Lua_T = std::variant<std::string, bool, double, int>;

class Configuration
{
    private:
        lua_State* state;
        LuaRef* values;
        std::string filename;
        std::unordered_map<std::string, Lua_T> elements;
        
        void createTable(std::vector<std::string>, Lua_T);

    public:
        Configuration();
        Configuration(std::string);
       ~Configuration();

        Configuration& addOption(std::string, std::string, Lua_T);

        LuaRef* getValues();

};

#endif // CONFIG_HPP
