#ifndef __ModuleSceneGame_H__
#define __ModuleSceneGame_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_LEVEL 2
struct SDL_Texture;
struct Mix_Chunk;

class ModuleSceneGame :
	public Module
{
private:
	int level = 1;

	SDL_Texture* background_graphics;
	iPoint level_dimensions;
	int font;
	int timer;

public:
	bool Start();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void onFadeInEnd();
	bool intro = false;
	int screen_enemies;
	Module* next;
	
	Mix_Chunk* intro_music;
	Mix_Chunk* newstart;

	iPoint getLevelDimensions() {
		return{ level_dimensions.x, level_dimensions.y - SCREEN_HEIGHT };
	}

	void setLevel(int lvl) { level = lvl; }
	int getLevel() { return level; }

	bool restart = false;

	ModuleSceneGame();
	virtual ~ModuleSceneGame();
};

#endif