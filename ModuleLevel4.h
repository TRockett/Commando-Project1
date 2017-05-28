#ifndef __ModuleLevel4_H__
#define __ModuleLevel4_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleSceneGame.h"
#include "Module.h"
class ModuleLevel4 :
	public ModuleSceneGame
{
public:
	ModuleLevel4();
	virtual ~ModuleLevel4();

	struct SDL_Texture;
	struct Mix_Chunk;
	
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void onFadeInEnd();

private:
	int timer1 = 0;
	bool spawning;
	int counter;
	};

#endif


