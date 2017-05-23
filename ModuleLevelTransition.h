#ifndef __ModuleLevelTransition_H__
#define __ModuleLevelTransition_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleInterface.h"

struct SDL_Texture;

class ModuleLevelTransition :
	public Module
{
public:
	
	ModuleLevelTransition();
	virtual ~ModuleLevelTransition();

private:
	SDL_Texture* background_graphics;
	int font_red, font_white;
	Animation trans;
	char* string_1 = "BROKE THE 3RD AREA NOW RUSH TO THE LAST AREA";
	Label* label;
	int actual = 0;
public:
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


};

#endif