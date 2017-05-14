#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include <functional>

#define MAX_ACTIVE_PARTICLES 100
#define PLAYER_BULLET_SPEED 5

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;
enum COLLIDER_TYPE;

enum PARTICLE_TYPE
{
	BULLET,
	BULLET_ENEMY,
	GRENADE_ENEMY,
	MISSILE,
	GRENADE_PLAYER,
	MOLOTOV,
	EXPLOSION,
	MORTAR_BOMB,
};

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	fPoint position;
	fPoint speed;
	bool parabol;
	Sint32 born = 0;
	Sint32 life = 0;
	bool fx_played = false;
	PARTICLE_TYPE particletype;
	Mix_Chunk* onEndSound = nullptr;
	float acceleration;
	fPoint init_speed;
	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};



class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, PARTICLE_TYPE particle_type, COLLIDER_TYPE collider_type = COLLIDER_NONE, Mix_Chunk* on_end_sound = nullptr, Sint32 delay = 0, bool parabol = 0);
	void addExplosionParticle(Particle* p);

	int fire_life = 100;
private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	

public:

	Particle explosion;
	Particle bullet;
	Particle grenade;
	Particle grenade_explosion;
	Particle fire_up;
	Particle fire_upleft;
	Particle fire_left;
	Particle fire_downleft;
	Particle fire_down;
	Particle fire_downright;
	Particle fire_right;
	Particle fire_upright;
	Particle molotov;
	Particle Bluefire_downleft;
	Particle Bluefire_down;
	Particle Bluefire_downright;
	Particle Missile_down;
	Particle Missile_downleft;
	Particle Missile_downright;
	Particle Mortar_bomb;
};

#endif // __MODULEPARTICLES_H__