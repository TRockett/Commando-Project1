#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
class _Mix_Music;
typedef _Mix_Music Mix_Music;

class ModuleSceneCongrats :
	public Module
{
private:
	SDL_Texture* background_graphics;
	int font_yellow, font_white;
	SDL_Texture* title_graphics;
	SDL_Texture* capcom;

	Mix_Music* music;

public:
	
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void onFadeInEnd();

	ModuleSceneCongrats();
	~ModuleSceneCongrats();
};

