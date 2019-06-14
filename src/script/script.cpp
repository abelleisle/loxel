#include <script/script.hpp>

namespace Script
{
    void stackDump (lua_State *L)
    {
        //lua_Debug info;
        //int level = 0;
        //while (lua_getstack(L, level, &info)) {
        //    lua_getinfo(L, "nSl", &info);
        //    printf("[%d] %s:%d -- %s [%s]\n",
        //        level, info.short_src, info.currentline,
        //        (info.name ? info.name : "<unknown>"), info.what);
        //    ++level;
        //}
        std::cout << "-----------------------------------------" << std::endl;
        int i;
        int top = lua_gettop(L);
        for (i = 1; i <= top; i++) {  /* repeat for each level */
            std::cout << i << ": ";
            int t = lua_type(L, i);
            switch (t) {

            case LUA_TSTRING:  /* strings */
                printf("`%s'", lua_tostring(L, i));
                break;

            case LUA_TBOOLEAN:  /* booleans */
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;

            case LUA_TNUMBER:  /* numbers */
                printf("%g", lua_tonumber(L, i));
                break;

            default:  /* other values */
                printf("%s", lua_typename(L, t));
                break;

            }
            std::cout << std::endl;
        }
        
        std::cout << "-----------------------------------------" << std::endl;
    }

    std::string tabs(int amt) 
    {
        std::string tmp;
        for (int i = 0; i < amt; i++)
            tmp += "    ";
        return tmp;
    }

    std::string printValue(std::string name, LuaRef value, int depth)
    {
        if (value.isNil())
            return "";

        std::string output;

        output += tabs(depth) + name + " = ";

        // TABLE //
        if (value.isTable()) {
            depth += 1;
            output += "{\n";
            for (auto &&p : pairs(value)) {
                output += printValue(p.first.cast<std::string>(), p.second, depth) + ",\n";
            }
            output += tabs(depth-1) + "}";
        // STRING //
        } else if (value.isString()) {
            output += "\"" + value.cast<std::string>() + "\"";
        // NUMBER //
        } else if (value.isNumber()) {
            output += value.cast<std::string>();
        // BOOLEAN //
        } else if (value.isBool()) {
            output += value.cast<bool>() ? 
                "true" :
                "false";
        }

        return output;
    }
}
