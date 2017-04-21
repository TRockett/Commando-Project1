#ifndef __ModuleObjects_H__
#define __ModuleObjects_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"


struct SDL_Texture;

class ModuleObjects :
	public Module
{
private:
	SDL_Texture* sprite_graphics;
	Animation tree1;
	Animation tree2;
	Animation rock;

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