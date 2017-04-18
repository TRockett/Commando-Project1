#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include <random>

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;

	// walk forward animation (arcade sprite sheet)

	e1_forward.PushBack({ 0, 220, 15, 23 });
	e1_forward.PushBack({ 16, 220, 15, 22 });
	e1_forward.PushBack({ 36, 220, 15, 23 });
	e1_forward.loop = true;
	e1_forward.speed = 0.15f;

	//walk diagonal down-left

	e1_down_left.PushBack({ 105,24,15,22 });
	e1_down_left.PushBack({ 120,24,15,22 });
	e1_down_left.PushBack({ 105,24,15,22 });
	e1_down_left.PushBack({ 137,24,15,22 });
	e1_down_left.speed = 0.15f;

	//walk diagonal down-right

	e1_down_right.PushBack({ 88,23,15,22 });
	e1_down_right.PushBack({ 56,23,15,22 });
	e1_down_right.PushBack({ 88,23,15,22 });
	e1_down_right.PushBack({ 73,23,15,22 });
	e1_down_right.speed = 0.15f;

	//walk diagonal up-right enemy

	e1_up_right.PushBack({ 0,246,17,22 });
	e1_up_right.PushBack({ 19,246,15,22 }, { 2,0 });
	e1_up_right.PushBack({ 44,246,16,21 });
	e1_up_right.PushBack({ 19,246,15,22 }, { 7,0 });
	e1_up_right.speed = 0.15f;

	//walk diagonal down-left

	e1_up_left.PushBack({ 97,47,15,22 });
	e1_up_left.PushBack({ 56,47,18,21 });
	e1_up_left.PushBack({ 97,47,15,22 });
	e1_up_left.PushBack({ 75,47,21,21 });
	e1_up_left.speed = 0.15f;

	//walk right animation enemyy


	e1_right.PushBack({ 78,246,16,22 });
	e1_right.PushBack({ 98,246,15,22 }, { 4,0 });
	e1_right.PushBack({ 78,246,16,22 });
	e1_right.PushBack({ 118,246,16,21 }, { 2,0 });
	
	e1_right.loop = true;
	e1_right.speed = 0.15f;


	//walk left annimation enemy

	e1_left.PushBack({ 0,246,17,22 });
	e1_left.PushBack({ 19,246,15,22 }, { 2,0 });
	e1_left.PushBack({ 44,246,16,21 });
	e1_left.PushBack({ 19,246,15,22 }, { 7,0 });
	e1_left.loop = true;
	e1_left.speed = 0.15f;

	//walk backward animation emey

	e1_backward.PushBack({ 0, 220, 15, 23 });
	e1_backward.PushBack({ 16, 220, 15, 22 });
	e1_backward.PushBack({ 36, 220, 15, 23 });
	e1_backward.loop = true;
	e1_backward.speed = 0.15f;
}


// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("rtype/enemies.png");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if(queue[i].pos.x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
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
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Move();

	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			if(enemies[i]->position.x * SCREEN_SIZE < App->render->camera.x - SPAWN_MARGIN
				|| enemies[i]->position.x * SCREEN_SIZE > (App->render->camera.x + SCREEN_WIDTH) * SCREEN_SIZE + SPAWN_MARGIN
				|| enemies[i]->position.y * SCREEN_SIZE < App->render->camera.y - SPAWN_MARGIN
				|| enemies[i]->position.y * SCREEN_SIZE > (App->render->camera.y + SCREEN_HEIGHT) * SCREEN_SIZE + SPAWN_MARGIN)
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
			/*case ENEMY_TYPES::REDBIRD:
			enemies[i] = new Enemy_RedBird(info.x,info.y);
			break;
			case ENEMY_TYPES::BROWNCOOKIE:
			int delay = rand() % 20 - 10;
			enemies[i] = new Enemy_BrownCookie(info.x, info.y, delay);
			break;*/
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
			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}