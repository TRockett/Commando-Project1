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
protected:
	SDL_Texture* background_graphics;
	iPoint level_dimensions;
	int font_red, font_white;
	int timer;

public:
	bool Start();
	char score_text[100];
	uint score = 0;
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void onFadeInEnd();
	bool intro = false;
	int screen_enemies;
	Module* next;
	int top_score;
	
	Mix_Chunk* intro_music;
	Mix_Chunk* newstart;

	iPoint getLevelDimensions() {
		return{ level_dimensions.x, level_dimensions.y - SCREEN_HEIGHT };
	}

	void setLevelDimensions(iPoint p) {
		level_dimensions = p;
	}


	bool restart = false;

	ModuleSceneGame();
	virtual ~ModuleSceneGame();
};

#endif