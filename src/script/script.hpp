#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <string>

#include <lua/lua.hpp>

class Script
{
    private:
        lua_State *state;
    public:
        Script();
       ~Script();

       lua_State* getState();
       void loadfile(std::string);
};

#endif // SCRIPT_HPP
