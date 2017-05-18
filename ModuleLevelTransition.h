#ifndef __ModuleLevelTransition_H__
#define __ModuleLevelTransition_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
struct SDL_Texture;

class ModuleLevelTransition :
	public Module
{
public:
	
	ModuleLevelTransition();
	virtual ~ModuleLevelTransition();

private:
	SDL_Texture* background_graphics;
	SDL_Texture* title_graphics;
	SDL_Texture* screen_welcome;
	SDL_Texture* capcom;
	int font_red, font_white;
	Animation welcome_anim;
	Animation screen_1;

public:
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


};

#endif