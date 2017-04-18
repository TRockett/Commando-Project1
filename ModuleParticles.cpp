#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("images/sprites.png");

	//bullet particles
	bullet.anim.PushBack({0,100,2,2});
	bullet.anim.speed = 0.2f;
	bullet.speed.y = -PLAYER_BULLET_SPEED;
	bullet.life = 3000;

	// explosion animation
	explosion.anim.PushBack({49, 96, 7, 7});
	explosion.anim.PushBack({60, 94, 16, 13});
	explosion.anim.PushBack({78, 92, 16, 14});
	explosion.anim.PushBack({95, 93, 16, 15});
	explosion.anim.PushBack({112, 94, 16, 13});
	explosion.anim.PushBack({130, 94, 15, 13});
	explosion.anim.speed = 0.15f;
	explosion.anim.loop = false;

	// grenade animation
	grenade.anim.PushBack({ 0,131,4,5 });
	grenade.anim.PushBack({ 4,5,5,6 });
	grenade.anim.PushBack({ 11 ,131,6,8 });

	// grenade explosion anim
	grenade_explosion.anim.PushBack({ 18,131,30,27 });
	grenade_explosion.anim.PushBack({ 48,131,21,23 });
	grenade_explosion.anim.PushBack({ 70,131,27,26 });
	grenade_explosion.anim.PushBack({ 99,131,32,32 });
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

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if(collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame().rect, collider_type, this);
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
		if(active[i] != nullptr && active[i]->collider == c1)
		{
			
			//AddParticle(explosion, active[i]->position.x-7, active[i]->position.y-5);
			delete active[i];
			active[i] = nullptr;
			break;
		}
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
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if(collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

