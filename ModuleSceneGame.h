#ifndef __ModuleSceneGame_H__
#define __ModuleSceneGame_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleInterface.h"
#include <string>

#define MAX_LEVEL 2
struct SDL_Texture;
struct Mix_Chunk;
class _Mix_Music;
typedef _Mix_Music Mix_Music;

class ModuleSceneGame :
	public Module
{
protected:
	SDL_Texture* background_graphics;
	iPoint level_dimensions;
	int font_red, font_white;
	Label* score_label;
	Label* grenade_label;
	int timer;
	std::string grenade_str;

public:
	bool Start();
	char score_text[100];
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void onFadeInEnd();
	bool intro = false;
	int screen_enemies;
	Module* next;
	
	Mix_Music* intro_music;
	Mix_Music* newstart;
	Mix_Music* music;

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