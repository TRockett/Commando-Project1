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
	int font_red, font_white;
	Animation trans;
	char* string_1 = "BROKE THE 3RD AREA";
	char* string_2;
	char* string_3 = "NOW RUSH TO THE LAST AREA";
	char* string_4;
	int actual = 0;
	int actual_2 = 0;
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