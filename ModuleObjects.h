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
	Animation door_bunker1;
	Animation door_bunker2;
	Animation door_bunker3;
	Animation door_bunker4;
	Animation door_bunker5;
	Animation door_bunker6;
	Animation door_bunker_left;
	Animation door_bunker_left1;
	Animation door_bunker_left2;
	Animation door_bunker_left3;

	Animation* helicopter;
	Animation helicopter1;
	Animation helicopter2;
	Animation helicopter3;
	Animation* helix;
	Animation helix1;
	Animation helix2;
	Animation helix3;

	//level 3

	Animation bunker_1;
	Animation bunker_2;
	Animation bunker_3;
	Animation bunker_4;


	Animation mortar_left1;
	Animation mortar_left2;
	Animation mortar_left3;
	Animation mortar_left4;

	Animation mortar_right1;
	Animation mortar_right2;
	Animation mortar_right3;
	Animation mortar_right4;

	Animation stones;
	int timer; 

	fPoint helipoint;
	float reduction;

	Collider* boxes[10];

	SDL_Rect objects[MAX_OBJECTS];

public:
	ModuleObjects();
	virtual ~ModuleObjects();
	Animation final_door;
	
	bool droping = false;
	bool Init();
	bool Start();
	
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

};

#endif