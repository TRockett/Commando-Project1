#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	bool CleanUp();
	update_status Update();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect* player_rect;
	Animation forward;
	Animation backward;
	Animation left;
	Animation right;
	Animation up_right;
	Animation up_left;
	Animation down_right;
	Animation down_left;
	iPoint position;
	iPoint direction;

};

#endif