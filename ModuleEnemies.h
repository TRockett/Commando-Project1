#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"

#define MAX_ENEMIES 30


enum ENEMY_TYPES
{
	
	NO_TYPE,
	LEFT_WEAPON,
	RIGHT_WEAPON,
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	iPoint pos;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;

	//Basic enemy animations

		//Enemy left weapon
	Animation e1_forward;
	Animation e1_backward;
	Animation e1_left;
	Animation e1_right;
	Animation e1_up_right;
	Animation e1_up_left;
	Animation e1_down_right;
	Animation e1_down_left;

		//Enemy right weapon
	Animation e2_forward;
	Animation e2_backward;
	Animation e2_left;
	Animation e2_right;
	Animation e2_up_right;
	Animation e2_up_left;
	Animation e2_down_right;
	Animation e2_down_left;
};

#endif // __ModuleEnemies_H__