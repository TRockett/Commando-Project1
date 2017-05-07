#ifndef __ModuleObjects_H__
#define __ModuleObjects_H__
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_OBJECTS 100

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
	Animation box;
	Animation box2;
	Animation box3;
	Animation door_bunker;
	Animation final_door;
	Animation* helicopter;
	Animation helicopter1;
	Animation helicopter2;
	Animation helicopter3;
	Animation* helix;
	Animation helix1;
	Animation helix2;
	Animation helix3;
	int timer; 

	fPoint helipoint;
	float reduction;

	Collider* boxes[10];

	SDL_Rect objects[MAX_OBJECTS];

public:
	ModuleObjects();
	virtual ~ModuleObjects();
	
	bool droping = false;
	bool Init();
	bool Start();
	
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

};

#endif