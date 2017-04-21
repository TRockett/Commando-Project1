#ifndef __ModuleObjects_H__
#define __ModuleObjects_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"


struct SDL_Texture;

class ModuleObjects :
	public Module
{
private:
	iPoint level_dimensions;
	SDL_Texture* sprite_graphics;
	Animation tree1;
	Animation tree2;
	Animation rock;
	Animation rock2;

public:
	ModuleObjects();
	virtual ~ModuleObjects();

	bool Init();
	bool Start();
	
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

};

#endif