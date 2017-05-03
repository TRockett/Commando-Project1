#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleParticles.h"

struct SDL_Texture;
struct Mix_Chunk;
struct Collider;

enum PLAYER_STATE : int {
	IDLE = 0,
	MOVING_UP = 1,
	MOVING_DOWN = 2,
	MOVING_RIGHT = 4,
	MOVING_LEFT = 8,
	MOVING_UP_RIGHT = 1 | 4,
	MOVING_UP_LEFT = 1 | 8,
	MOVING_DOWN_RIGHT = 2 | 4,
	MOVING_DOWN_LEFT = 2 | 8,
	DEAD = -1
};

PLAYER_STATE operator |(PLAYER_STATE p, PLAYER_STATE s);

fPoint tofPoint(iPoint a);
iPoint toiPoint(fPoint a);


class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	bool CleanUp();
	update_status Update();
	void OnCollision(Collider*, Collider*);
	PLAYER_STATE state = IDLE;
	bool grenade_on = false;
	bool bthrowing;
	int intro_state;
	fPoint init_pos;
	float parabol = 0.65f;
	Mix_Chunk* grenade_explosion;
	fPoint position;
	iPoint GetPosition() {
		return toiPoint(position);
	}
	int lives;
	uint grenades;

private:
	SDL_Texture* graphics = nullptr;
	SDL_Texture* godmode = nullptr;
	Animation* current_animation = nullptr;
	Animation forward;
	Animation backward;
	Animation left;
	Animation right;
	Animation up_right;
	Animation up_left;
	Animation down_right;
	Animation down_left;
	Animation death;
	Animation drown;
	Animation leave_heli;
	Animation bye_anim;
	Animation throw_grenade;

	fPoint prev_position;
	Mix_Chunk* shoot;
	Collider* collider;
	Particle fire;	//Fire shot particle
	Animation bridge;
	Animation bridge2;
	float grenade_speed;
	bool b_godmode;
	
	PLAYER_STATE prev_state = IDLE;
	bool shooting;
	bool grenade1;


	int speed;
	int player_min_y;
	int shooting_angle;
	int direction;
	iPoint shooting_position;

	void checkInput();
	void processInput();
	void wallCollision();
	void waterCollision();
	void enemyCollision();
	void rotateShootingAngle();

	void Drown();

};

#endif