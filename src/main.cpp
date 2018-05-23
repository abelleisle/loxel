//#include <LuaJIT/lua.hpp>
#include <lua5.3/lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include <client/client.hpp>

class Vec2 {
public:
    int x;
    int y;
    Vec2(int _x, int _y):x(_x), y(_y){}
};

class Vec3 {
public:
    int x;
    int y;
    int z;
    Vec3(int _x, int _y, int _z):x(_x),y(_y),z(_z){}
};

class Block {
private:
    std::string name;
    std::string model;
    int id;
    int durability;
    int onClick;
    
public:
    Block() {}
    ~Block() {}

    void setName(std::string n) {this->name = n;}  
    void setModel(std::string m) {this->model = m;}
    void setID(int id) {this->id = id;}
    void setDurability(int d) {this->durability = d;}
    void setOnClick(int f) {this->onClick = f;}

    std::string getName() {return name;}
    std::string getModel() {return model;}
    int getID() {return id;}
    int getDurability() {return durability;}
    int getOnClick() {return onClick;}

    void click(lua_State *L) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, onClick);
        lua_pcall(L, 0, 0, 0);
    }

    friend std::ostream &operator<<(std::ostream &os, Block &o) {
        os << "Name: " << o.getName() << std::endl
           << "Model: " << o.getModel() << std::endl
           << "ID: " << o.getID() << std::endl
           << "Durability: " << o.getDurability() << std::endl
           << "On-Click func: " << o.getOnClick() << std::endl; 
        return os;
    }
};

class Chunk {
private:
    Vec3 offset;   
    const static Vec3 size;

public:
    Chunk(Vec3 offset):offset(offset){}
    //Chunk generate(){return this;}
};

class World {
private:
    std::vector<Block> blocks;
    lua_State *L;

public:
    World(){}
    ~World(){}

    void createLuaInstance(lua_State *L) {
        this->L = L;
    }

    void addBlock(Block b) {blocks.push_back(b);}
    void printBlocks() {
        for (auto &b : blocks) {
            std::cout << b;
            b.click(L);
            std::cout << std::endl;
        }
    }
};

static void stackDump (lua_State *L)
{
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
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
        printf("  ");  /* put a separator */
    }
    
    printf("\n");  /* end the listing */
}

static World w;

static int create_block(lua_State *L)
{
    Block b;

    std::string name;
    std::string tmps;
    int tmpn;
    bool tmpb;
    int tmpf;

    for (lua_pushnil(L); lua_next(L, -2) != 0; lua_pop(L, 1)) {
        name = lua_tostring(L, -2);
        int t = lua_type(L, -1);
        switch(t) {
        case LUA_TSTRING:
            tmps = lua_tostring(L, -1);
            break;
        case LUA_TBOOLEAN:
            tmpb = lua_toboolean(L, -1);
            break;
        case LUA_TNUMBER:
            tmpn = lua_tonumber(L, -1);
            break;
        case LUA_TFUNCTION:
            tmpf = luaL_ref(L, LUA_REGISTRYINDEX);
            lua_pushvalue(L, 1);
            break;
        default:
            std::cout << lua_typename(L, t);
        }
        
        if (name == "name") {
           b.setName(tmps);
        } else if (name == "id") {
            b.setID(tmpn);
        } else if (name == "durability") {
            b.setDurability(tmpn);
        } else if (name == "model") {
            b.setModel(tmps);
        } else if (name == "onclick") {
            b.setOnClick(tmpf);
        } else {
            (void)tmpb;
        }
    }
    
    w.addBlock(b);
    return 0;
}

int main()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "create_block", create_block);

    luaL_loadfile(L, "scripts/load.lua");
    lua_pcall(L, 0, 0, 0);

    //lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    //lua_pcall(L, 0, 0, 0);

    stackDump(L);
    
    w.createLuaInstance(L);
    w.printBlocks();

    lua_close(L);

    Game *c = new Client();
    c->init();

    return 0;
}

/*int main(int argc, char** argv)
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    auto n = atoi(argv[1]);

    int status = luaL_loadfile(L, "hello.lua");
    
    int ret = lua_pcall(L, 0, 0, 0); // execute once to assign functions
    if (ret != 0) {
        std::cerr << lua_tostring(L, -1);
        return -1;
    }

    lua_getglobal(L, "fact"); // function to be called
    lua_pushnumber(L, n); // push argument
    stackDump(L);
    stackDump(L);
    
    if (lua_pcall(L, 1, 1, 0) != 0) { // one arg, one return value
        std::cerr << lua_tostring(L, -1);
        return -1;
    }

    auto res = lua_tonumber(L, -1);
    lua_pop(L, 1); // pop returned value
    std::cout << "Fact: " << res << std::endl;
    
    lua_getglobal(L, "Coins");
    if (lua_istable(L, -1)) {
        std::cout << "IS TABLE" << std::endl;
        lua_pushnumber(L, 1);
        lua_gettable(L, -1);
        stackDump(L);
    }
    stackDump(L);

    lua_close(L);

    return 0;
}*/

