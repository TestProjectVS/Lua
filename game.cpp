#include "game.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

using namespace std;

Game::Game()
{
	srand ( time(NULL) );
}

Game::~Game()
{
}

int game_random(lua_State *l)
{
	int argc = lua_gettop(l);
	if(argc != 2)
		luaL_error(l, "random needs two arguments");
	int start = lua_tointeger(l,1);
	int end = lua_tointeger(l,2);
	int random = rand()%(end-start+1)+start;
	lua_pushinteger(l,random);
	return 1; // number of return values
}

int game_print(lua_State *l)
{
	string output;
	int argc = lua_gettop(l);

	for ( int n=1; n<=argc; ++n ) {
		output += lua_tostring(l, n);
	}

	cout << output.c_str() << endl;
	return 0; // number of return values
}

// global functions
static const luaL_reg game_funcs[] = 
{
	{ "random",			game_random},
	{ "print",			game_print },
	{ NULL,				NULL }
};

void Game::RegisterLua(lua_State* l)
{
	luaL_register(l, "game", game_funcs);
	lua_settop(l, 0);
}
void Game::Run(lua_State *l)
{
	while(true)
	{
		CallBehaviour(l);
		system("PAUSE");
	}

}
int Game::CallBehaviour(lua_State *l)
{
	lua_getglobal(l, "behaviour");
	lua_pcall(l,0,1,0);
	lua_settop(l, 0);
	return 0;
}