#ifndef __ModuleLevel3_H__
#define __ModuleLevel3_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;
class ModuleLevel3 :
	public Module
{
private:


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



	bool restart = false;

	ModuleLevel3();
	virtual ~ModuleLevel3();
};

#endif