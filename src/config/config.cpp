#include <config/config.hpp>

#include <iostream>

Configuration::Configuration()
{

}

Configuration::Configuration(std::string file)
{
    filename = file;
    state = luaL_newstate();
    values = new LuaRef(state);
    
    luaL_openlibs(state);
    if (luaL_loadfile(state, file.c_str()) || lua_pcall(state, 0, 0, 0)) {
        std::cout << "Configuration file not found" << std::endl;
    }
}

void Configuration::createTable(std::vector<std::string> tokens,
                                Lua_T value)
{
    //bool entered = false;
    (void)value;
    bool createdRoot = false;

    /********************
    *  GET ROOT TABLE  *
    ********************/
    
    std::string root = tokens.front();
    tokens.erase(tokens.begin());

    lua_getglobal(state, root.c_str()); // get the root table
    if (lua_isnil(state, 1)) {// if table doesn't exist, create it
        lua_pop(state, 1);
        lua_newtable(state);
        createdRoot = true;
    }


    /*****************************
    *  DESCEND INTO SUB-TABLES  *
    *****************************/
    
    long unsigned int i = 0;
    for (; i < tokens.size()-1; i++) {
        std::string token = tokens.front();
        tokens.erase(tokens.begin());

        std::cout << "a" << std::endl;
        Script::stackDump(state);
        lua_pushstring(state, token.c_str());
        Script::stackDump(state);
        lua_gettable(state, -2); // get root[token]
        Script::stackDump(state);
        std::cout << "b" << std::endl;
        if (lua_isnil(state, -1)) { // if inner table doesn't exist
            lua_remove(state, lua_gettop(state));
            lua_pushstring(state, token.c_str());
            lua_newtable(state);
        } else {
            Script::stackDump(state);
        }
        std::cout << "c" << std::endl;
    }


    /****************
    *  CREATE KEY  *
    ****************/

    std::string key = tokens.front();
    tokens.erase(tokens.begin());

    lua_pushstring(state, key.c_str());
    lua_pushstring(state, "test");

    Script::stackDump(state);

    /****************************
    *  BACK OUT OF SUB-TABLES  *
    ****************************/
    
    for (long unsigned int u = 0; u <= i; u++) {
        lua_settable(state, -3);
    }

    /*********************
    *  NAME ROOT TABLE  *
    *********************/
    
    if (createdRoot) {
        lua_setglobal(state, root.c_str()); // name the root table
    }

        //LuaRef g = getGlobal(state, token.c_str());

        //if (g.isNil()) {
        //    lua_newtable(state);
        //    createTable(tokens, value);
        //    lua_setglobal(state, token.c_str());
        //} else {
        //    // see if inner table exists
        //    lua_getfield(state, -1, token.c_str());
        //    if (lua_type(state, -1) != LUA_TNIL) {
        //        lua_pushstring(state, token.c_str());
        //        lua_newtable(state);
        //        createTable(tokens, value);
        //        lua_settable(state, -3);
        //    } else {
        //        lua_next(state, -2);
        //        createTable(tokens, value);
        //        lua_settable(state, -3);
        //    }
        //}

    //size_t pos = group.find(".");
    //if (pos != std::string::npos || (pos = std::string::npos && 
    //                                 group.size() != 0)) {

    //    std::string token;
    //    if (pos == std::string::npos) {
    //        token = group;
    //        group = "";
    //    } else {
    //        token = group.substr(0,pos);
    //        group = group.substr(pos);
    //    }

    //    std::cout << token << std::endl;
    //    std::cout << group << std::endl;

    //} else {
    //}


        //entered = true;
        //LuaRef g = getGlobal(state, token.c_str());
        //if (g.isNil()) {
        //    lua_newtable(state);
        //    createTable(group, key, value);
        //    lua_setglobal(state, token.c_str());
        //} else {
        //    lua_pushstring(state, token.c_str());
        //    lua_newtable(state);
        //    createTable(group, key, value);
        //    lua_settable(state, -3);
        //}
        
    //if (!entered) {
    //    lua_pushstring(state, key.c_str());
    //    lua_pushstring(state, "test");
    //    lua_settable(state, -3);
    //}
}

Configuration& Configuration::addOption(std::string group,
                                        std::string key,
                                        Lua_T value)
{
    std::istringstream stream_group(group);
    std::vector<std::string> tokens;
    std::string token;

    //(void)value;

    while(std::getline(stream_group, token, '.')) {
        tokens.emplace_back(token);
    }
    tokens.emplace_back(key);

    //lua_getglobal(state, "client");

    //if (lua_isnil(state, 1)) {
    //    std::cout << "No table" << std::endl;
    //    lua_newtable(state);

    //    lua_setglobal(state, "client");
    //} else {
    //    std::cout << "Root table" << std::endl;
    //}

    ////lua_getfield(state, 1);

    //Script::stackDump(state);
    //lua_pop(state, 1);

    createTable(tokens, value);

    //std::cout << this << std::endl;

    //// Get the root table
    //std::getline(stream_group, token, '.');
    //*values = getGlobal(state, token.c_str());
    ////*values = LuaRef(state, token.c_str());
    //std::cout << token << " table" << std::endl;
    //// If it doesn't exist, create it
    //if (values->isNil()) {
    //    *values = LuaRef(state, token.c_str());
    //    *values = newTable(state);
    //    std::cout << "Creating new table" << std::endl;
    //} else {
    //    std::cout << "table exists" << std::endl;
    //}

    //root = token;
    //LuaRef setting = *values;

    // Get the rest of the tables
    //while(std::getline(stream_group, token, '.')) {
    //    LuaRef s = setting;
    //    if (s[token.c_str()].isNil()) {
    //        s[token.c_str()] = newTable(state);
    //    }
    //    setting = s[token.c_str()];
    //}

    //(void)value;

    //setting[key] = 69;

    //*values = getGlobal(state, root.c_str());
    //if (!values->isNil())
    //    (*values)["b"]["c"]["d"][key.c_str()] = 45;
    //else {
    //    lua_newtable(state);
    //    {
    //        lua_pushliteral(state, "b");
    //        lua_newtable(state);
    //        {
    //            lua_pushliteral(state, "c");
    //            lua_newtable(state);
    //            {
    //                lua_pushliteral(state, "d");
    //                lua_newtable(state);
    //                {
    //                    lua_pushliteral(state, "e");
    //                    lua_pushstring(state, "test");
    //                    lua_settable(state, -3);
    //                }
    //                lua_settable(state, -3);
    //            }
    //            lua_settable(state, -3);
    //        }
    //        lua_settable(state, -3);
    //    }
    //    lua_setglobal(state, "client");
    //}

    //lua_pcall(state, 0, 0, 0);

    Script::stackDump(state);
    *values = getGlobal(state, "client");
    std::cout << Script::printValue("client", *values) << std::endl;

    return *this;
}

Configuration::~Configuration()
{
    delete values;
    lua_close(state);
}

LuaRef* Configuration::getValues()
{
    return values;
}
