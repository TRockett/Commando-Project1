#ifndef __ModuleLevel3_H__
#define __ModuleLevel3_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleSceneGame.h"

struct SDL_Texture;
struct Mix_Chunk;
class ModuleLevel3 :
	public ModuleSceneGame
{
private:
	int timer;
	bool spawning;
	int counter;
public:
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void onFadeInEnd();

	ModuleLevel3();
	virtual ~ModuleLevel3();
};

#endif