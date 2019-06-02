#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <lua/lua.hpp>
#include <LuaBridge/LuaBridge.h>

using namespace luabridge;

namespace Script
{
    void stackDump(lua_State*);
    std::string printValue(std::string, LuaRef, int d = 0);
    void print_table(lua_State*);
}

#endif //SCRIPT_HPP
