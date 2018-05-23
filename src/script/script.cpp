#include <script/script.hpp>
#include <script/script_exception.hpp>

Script::Script()
{
    state = luaL_newstate();
    luaL_openlibs(state);
}

Script::~Script()
{
    //::operator delete(state);
    lua_close(state);
}

lua_State* Script::getState()
{
    return state;
}

void Script::loadfile(std::string filename)
{
    if(luaL_loadfile(state, filename.c_str()) != 0)
        throw ScriptException::FileNotFound(filename);

}
