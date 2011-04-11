#ifndef GAME_H
#define GAME_H
#include <string>
using namespace std;
struct lua_State;

class Game
{
public:
	Game();
	~Game();
	void RegisterLua(lua_State* l);
	void Run(lua_State *l);
private:
	static int CallBehaviour(lua_State *l);
};
#endif