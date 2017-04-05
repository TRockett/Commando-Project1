#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;
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
	Animation* current_animation = nullptr;
	Animation forward;
	Animation idle_forward;
	Animation idle_backward;
	Animation idle_right;
	Animation idle_left;
	Animation idle_up_left;
	Animation idle_down_left;
	Animation idle_up_right;
	Animation idle_down_right;
	Animation backward;
	Animation left;
	Animation right;
	Animation up_right;
	Animation up_left;
	Animation down_right;
	Animation down_left;
	iPoint position;
	iPoint direction;
	Mix_Chunk* shoot;

};

#endif