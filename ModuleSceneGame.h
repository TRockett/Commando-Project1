#ifndef __ModuleSceneGame_H__
#define __ModuleSceneGame_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_LEVEL 2
struct SDL_Texture;


class ModuleSceneGame :
	public Module
{
private:
	int level;
	p2Point<int> initial_camera_pos;
	SDL_Texture* background_graphics;
	int targetY = 0;
	bool moving = false;

public:
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void onFadeInEnd();

	void setLevel(int lvl) { level = lvl; }
	int getLevel() { return level; }

	ModuleSceneGame();
	~ModuleSceneGame();
};

#endif