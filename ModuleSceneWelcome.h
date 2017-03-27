#ifndef __ModuleSceneWelcome_H__
#define __ModuleSceneWelcome_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#define BACKGROUND_NUMBER 3

struct SDL_Texture;

class ModuleSceneWelcome :
	public Module
{
private:
	SDL_Texture* background_graphics[BACKGROUND_NUMBER];
	//SDL_Texture* sprite_graphics;

	float image_index;
	int last_image = 0;

public:
	float speed;

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