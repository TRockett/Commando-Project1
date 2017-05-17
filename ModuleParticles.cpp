#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleSound.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;


	// explosion animation
	explosion.anim.PushBack({ 49, 96, 7, 7 }, { 3, 3 });
	explosion.anim.PushBack({ 60, 94, 16, 13 }, { 8, 6 });
	explosion.anim.PushBack({ 78, 92, 16, 14 }, { 8, 7 });
	explosion.anim.PushBack({ 95, 93, 16, 15 }, { 8, 7 });
	explosion.anim.PushBack({ 112, 94, 16, 13 }, { 8, 6 });
	explosion.anim.PushBack({ 130, 94, 15, 13 }, { 7, 6 });
	explosion.anim.speed = 0.15f;
	explosion.anim.loop = false;

	//bullet particles
	bullet.anim.PushBack({ 0, 100, 2, 2 }, { 1, 1 });
	bullet.anim.speed = 0.2f;
	bullet.speed.y = PLAYER_BULLET_SPEED;
	bullet.life = 300;


	// grenade animation
	grenade.anim.PushBack({ 0, 131, 4, 5 }, { 2, 2 });
	grenade.anim.PushBack({ 4,131,5,6 }, { 2, 3 });
	grenade.anim.PushBack({ 11,131,6,8 }, { 3, 4 });
	grenade.anim.PushBack({ 4,131,5,6 }, { 2, 3 });
	grenade.anim.PushBack({ 0,131,4,5 }, { 2, 2 });

	grenade.life = 1200;
	grenade.anim.speed = 0.07f;
	grenade.anim.loop = false;

	// grenade explosion anim
	grenade_explosion.anim.PushBack({ 18,131,30,27 }, { 15, 13 });
	grenade_explosion.anim.PushBack({ 48,131,21,23 }, { 10, 11 });
	grenade_explosion.anim.PushBack({ 70,131,27,26 }, { 13, 13 });
	grenade_explosion.anim.PushBack({ 99,131,32,32 }, { 16, 16 });
	grenade_explosion.anim.loop = false;
	grenade_explosion.anim.speed = 0.25f;

	// fire
	fire_up.anim.PushBack({ 0, 113, 5,6 });
	fire_up.anim.loop = false;
	fire_up.life = fire_life;

	fire_upright.anim.PushBack({ 7,113,6,6 });
	fire_upright.anim.loop = false;
	fire_downright.life = fire_life;

	fire_right.anim.PushBack({ 15,113,8,5 });
	fire_right.anim.loop = false;
	fire_right.life = fire_life;

	fire_left.anim.PushBack({ 24,113,8,5 });
	fire_left.anim.loop = false;
	fire_left.life = fire_life;

	fire_down.anim.PushBack({ 0,121,5,6 });
	fire_down.anim.loop = false;
	fire_down.life = fire_life;

	fire_upleft.anim.PushBack({ 8,121,6,6 });
	fire_upleft.anim.loop = false;
	fire_upleft.life = fire_life;

	fire_downleft.anim.PushBack({ 16,121,6,6 });
	fire_downleft.anim.loop = false;
	fire_downleft.life = fire_life;

	fire_downright.anim.PushBack({ 24,121,6,6 });
	fire_downright.anim.loop = false;
	fire_downright.life = fire_life;

	molotov.anim.PushBack({ 1441,428,10,4 });
	molotov.life = 600;
	molotov.anim.loop = false;

	Bluefire_down.anim.PushBack({ 56,113,7,11 });
	Bluefire_down.life = fire_life;
	Bluefire_down.anim.speed = 0.2f;
	Bluefire_down.anim.loop = false;

	Bluefire_downleft.anim.PushBack({ 46,113,9,9 });
	Bluefire_downleft.life = fire_life;
	Bluefire_downleft.anim.speed = 0.2f;
	Bluefire_downleft.anim.loop = false;

	Bluefire_downright.anim.PushBack({ 36,113,9,9 });
	Bluefire_downright.life = fire_life;
	Bluefire_downright.anim.speed = 0.2f;
	Bluefire_downright.anim.loop = false;

	Missile_down.anim.PushBack({ 89,113,5,10 });
	Missile_down.life = 6000;
	Missile_down.anim.speed = 0.2f;
	Missile_down.anim.loop = false;

	Missile_downright.anim.PushBack({ 96,113,7,9 });
	Missile_downright.life = 6000;
	Missile_downright.anim.speed = 0.2f;
	Missile_downright.anim.loop = false;

	Missile_downleft.anim.PushBack({ 104,113,7,9 });
	Missile_downleft.life = 6000;
	Missile_downleft.anim.speed = 0.2f;
	Missile_downleft.anim.loop = false;

	Mortar_bomb.anim.PushBack({ 121,113,6,5 });
	Mortar_bomb.anim.PushBack({ 112,113,8,7 });
	Mortar_bomb.life = 1500;
	Mortar_bomb.anim.speed = 0.2f;
	Mortar_bomb.anim.loop = false;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("images/sprites.png");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		Sint32 ticks = SDL_GetTicks();
		if(p->Update() == false)
		{
			addExplosionParticle(p);

			if (p->onEndSound != nullptr)
				App->sound->PlaySound(p->onEndSound, 0);

			delete p;
			active[i] = nullptr;
		}
		else if(ticks >= p->born)
		{
			AnimationFrame frame = p->anim.GetCurrentFrame();
			App->render->Blit(graphics, p->position.x - frame.pivot.x, p->position.y - frame.pivot.y, &(frame.rect));
			if(p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

 void ModuleParticles::AddParticle(const Particle& particle, int x, int y, PARTICLE_TYPE particle_type, COLLIDER_TYPE collider_type, Mix_Chunk* on_end_sound, Sint32 delay, bool parabol)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->position.x = x;
			p->position.y = y;
			p->born = SDL_GetTicks() + delay;
			p->particletype = particle_type;
			p->onEndSound = on_end_sound;
			p->parabol = parabol;
			if (collider_type != COLLIDER_NONE) {
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame().rect, collider_type, this);
				p->collider->active = false;
			}
			active[i] = p;
			break;
		}
		
	}

}

// TODO 5: Make so every time a particle hits a wall it triggers an explosion particle
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if(active[i] != nullptr && active[i]->collider == c1 && active[i]->particletype != EXPLOSION)
		{
			Particle* p = active[i];
			addExplosionParticle(p);

			if (p->onEndSound != nullptr)
				App->sound->PlaySound(p->onEndSound, 0);

			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

void ModuleParticles::addExplosionParticle(Particle* p) {
	int x = p->position.x + p->anim.frames[p->anim.getFrameIndex()].pivot.x;
	int y = p->position.y + p->anim.frames[p->anim.getFrameIndex()].pivot.y;
	switch (p->particletype) {
	case GRENADE_PLAYER:
		AddParticle(grenade_explosion, x, y, EXPLOSION, COLLIDER_PLAYER_SHOT);
		App->player->grenade_on = false;
		break;
	case GRENADE_ENEMY:
	case MOLOTOV:
	case MORTAR_BOMB:
		AddParticle(grenade_explosion, x, y, EXPLOSION, COLLIDER_ENEMY_SHOT);
		App->player->grenade_on = false;
		break;
	case BULLET:
		AddParticle(explosion, x, y, EXPLOSION, COLLIDER_NONE);
		break;
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life),acceleration(p.acceleration)
{
	acceleration = -0.3f;
	init_speed = p.speed;
}

Particle::~Particle()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Particle::Update()
{
	bool ret = true;

	Sint32 ticks = SDL_GetTicks();

	if (parabol == true)
	{
		if (init_speed.y + 0.5 >= (speed.y + acceleration))
		{
			speed.y = speed.y + acceleration;
			acceleration = acceleration + 0.05f;
		}
	}
	if(life > 0)
	{
		if ((ticks - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	if (ticks >= born) {
		if (collider != nullptr)
			collider->active = true;
		position.x += speed.x;
		position.y += speed.y;
	}

	if(collider != nullptr)
		collider->SetPos(position.x - anim.frames[anim.getFrameIndex()].pivot.x, position.y - anim.frames[anim.getFrameIndex()].pivot.y);

	return ret;
}

