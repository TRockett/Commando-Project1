#ifndef __ModuleSceneWelcome_H__
#define __ModuleSceneWelcome_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneWelcome :
	public Module
{
private:
	SDL_Texture* background_graphics;
	SDL_Texture* title_graphics;
	SDL_Texture* screen_welcome;
	SDL_Texture* capcom;
	int font;
	Animation welcome_anim;
	Animation screen_1;
public:
	char score_text[100];
	uint score = 0;
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	ModuleSceneWelcome();
	~ModuleSceneWelcome();
};

#endif