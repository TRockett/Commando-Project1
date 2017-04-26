#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "EnemyLeft.h"
#include <random>
#include <time.h>
#include "EnemyMoto.h"
#include "EnemyJump.h"
#include "ModuleSceneGame.h"
#include "EnemyGrenade.h"
#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	srand(time(nullptr));

	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;

}


// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("Images/sprites.png");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if(!(queue[i].pos.x < (App->render->camera.x / SCREEN_SIZE) - SPAWN_MARGIN
				|| queue[i].pos.x >((App->render->camera.x / SCREEN_SIZE) + SCREEN_WIDTH) + SPAWN_MARGIN
				|| queue[i].pos.y < abs(App->render->camera.y / SCREEN_SIZE) - SPAWN_MARGIN
				|| queue[i].pos.y >(abs(App->render->camera.y / SCREEN_SIZE) + SCREEN_HEIGHT) + SPAWN_MARGIN))
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].pos.x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr) enemies[i]->Move();
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			if(enemies[i]->position.x < (App->render->camera.x / SCREEN_SIZE) - SPAWN_MARGIN
				|| enemies[i]->position.x > ((App->render->camera.x / SCREEN_SIZE) + SCREEN_WIDTH) + SPAWN_MARGIN
				|| enemies[i]->position.y < abs(App->render->camera.y / SCREEN_SIZE) - SPAWN_MARGIN
				|| enemies[i]->position.y > (abs(App->render->camera.y / SCREEN_SIZE) + SCREEN_HEIGHT) + SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].pos.x = x;
			queue[i].pos.y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for(; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if(i != MAX_ENEMIES)
	{
		switch(info.type)
		{
			case ENEMY_TYPES::LEFT_WEAPON:
				enemies[i] = new EnemyLeft(info.pos.x,info.pos.y);
				break;

			case ENEMY_TYPES::MOTO_TYPE:
				enemies[i] = new EnemyMoto(info.pos.x, info.pos.y);
				break;
			
			case ENEMY_TYPES::JUMPING_ENEMY:
				enemies[i] = new EnemyJump(info.pos.x, info.pos.y);
				break;
			case ENEMY_TYPES::ENEMY_GRENADE:
				enemies[i] = new EnemyGrenade(info.pos.x, info.pos.y);
				break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2);
			break;
		}
	}
}

bool ModuleEnemies::EraseEnemy(Enemy* enemy) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i] == enemy) {
			delete enemies[i];
			enemies[i] = nullptr;
			return true;
		}
	}
	return false;
}