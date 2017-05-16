#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleSceneCongrats :
	public Module
{
private:
	SDL_Texture* background_graphics;
	int font_red, font_white;
	SDL_Texture* title_graphics;
	SDL_Texture* capcom;
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

