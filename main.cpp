#include <iostream>
#include "string"
#include "game.h"
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
using namespace std;
/*
Declare the Lua libraries we wish to use.
Any libraries used from the lua scripts loaded later must be present here.
*/
static const luaL_reg lualibs[] =
{
	{ "base",       luaopen_base },
	{ NULL,         NULL }
};

/* A function to open up all the Lua libraries you declared above. */
static void openlualibs(lua_State *l)
{
	const luaL_reg *lib;

	for (lib = lualibs; lib->func != NULL; lib++)
	{
		lib->func(l);
		lua_settop(l, 0);
	}
}

int MyLuaError(lua_State *l)
{
	cerr << "Failed to execute the lua script:" << endl;
	cerr << lua_tostring(l, -1) << endl;
	lua_pop(l, 1); // pop the error msg from the stack
	return 1;
}

int main(int argc, char** argv)
{
	Game game;
	lua_State *l;
	l = lua_open();
	game.RegisterLua(l);

	int rv = 0;
	
	rv = luaL_dofile(l, "script.lua");
	if(rv != 0)
	{
		return MyLuaError(l);
	}
	game.Run(l);
	lua_close(l);
	return 0;
}