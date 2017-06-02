#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"

#define MAX_ENEMIES 50
#define MAX_SPAWNERS 15
#define SPAWN_MARGIN 100


enum ENEMY_TYPE
{

	NO_TYPE,
	LEFT_WEAPON,
	MOTO_TYPE,
	ENEMY_GRENADE,
	ENEMY_BAZOOKA,
	MOTOLEVEL3,
	COMMANDER,
	ENEMY_MORTAR,
	ENEMY_TRUCK,
	ENEMY_TOWER,
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPE type = ENEMY_TYPE::NO_TYPE;
	iPoint pos;
	int angle;
	int sub_type;
	bool isglobal;
};

struct EnemySpawner {
	EnemyInfo info;
	iPoint pos;
	iPoint absolute_deviation;
	int delay_frames;
	bool global = false;
	int frames_since_prev_spawn = 0;
	Animation* anim_triggered;
	bool active = true;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	Enemy* enemies[MAX_ENEMIES];

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPE type, int x, int y, int angle, int sub_type);
	EnemySpawner* AddSpawner(ENEMY_TYPE type, int x, int y, int angle, int delay, int sub_type = 0, bool global = false, Animation* anim_triggered = nullptr, int abs_x = 0, int abs_y = 0);
	bool EraseEnemy(Enemy* enemy);

private:

	bool SpawnEnemy(const EnemyInfo& info);
	void SpawnerSpawn(EnemySpawner& spawner);

	EnemyInfo queue[MAX_ENEMIES];

	EnemySpawner* spawners[MAX_SPAWNERS];
	SDL_Texture* sprites;
	

public:
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

	bool dead;
};

#endif // __ModuleEnemies_H__