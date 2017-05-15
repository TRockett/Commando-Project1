#pragma once
#include "Enemy.h"
#include "Path.h"

class EnemyTruck :
	public Enemy
{
public:
	EnemyTruck(int x, int y, int angle, int sub_type);
	~EnemyTruck();

	virtual void Move();
private:
	Path movement;

	Animation jump;
	Animation walk;
	Animation jump_l;
	Animation walk_l;


	int current_angle;

	bool disappear = false;
	int timer;
	bool jumping = false;
	float jump_speed = -0.5f;
	int jump_state = 0;
	int direction;
	iPoint shooting_position;
};

