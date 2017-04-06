#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;
struct Collider;

enum PLAYER_STATE : int {
	IDLE = 0,
	MOVING_UP = 1,
	MOVING_DOWN = 2,
	MOVING_RIGHT = 4,
	MOVING_LEFT = 8,
	SHOOTING = 16,
	MOVING_UP_RIGHT = 1 | 4,
	MOVING_UP_LEFT = 1 | 8,
	MOVING_DOWN_RIGHT = 2 | 4,
	MOVING_DOWN_LEFT = 2 | 8
};

PLAYER_STATE operator |(PLAYER_STATE p, PLAYER_STATE s) {
	PLAYER_STATE ret = static_cast<PLAYER_STATE>((int)p | (int)s);
	return ret;
}

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	bool CleanUp();
	update_status Update();
	void OnCollision(Collider*, Collider*);

private:
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
	iPoint direction_animations;
	Mix_Chunk* shoot;
	Collider* collider;

	PLAYER_STATE state = IDLE;
	PLAYER_STATE prev_state = IDLE;


	int speed;

};

#endif