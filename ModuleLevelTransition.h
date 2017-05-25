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
	const char* string_1 = "BROKE THE 3RD AREA\nNOW RUSH TO THE LAST AREA";
	char* new_str = "";
	Label* label;
	
	int actual = 0;
	int timer = 0;
public:
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


};

#endif