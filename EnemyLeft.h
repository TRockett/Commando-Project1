#pragma once
#include "Enemy.h"
#include "Path.h"

class EnemyLeft :
	public Enemy
{

private:
	Path movement;

	Animation e1_forward;
	Animation e1_backward;
	Animation e1_left;
	Animation e1_right;
	Animation e1_up_right;
	Animation e1_up_left;
	Animation e1_down_right;
	Animation e1_down_left;
	Animation death;
	Animation jump;
	Animation walk;


	int current_angle;
	bool collision = false;
	bool dying = false;
	bool disappear = false;
	int timer;
	bool jumping = false;
	float jump_speed = -3;
	int jump_state = 0;
	int direction;
	iPoint shooting_position;

public:
	EnemyLeft(int x, int y, int angle, int sub_type);

	virtual ~EnemyLeft();
	virtual void Move();
	virtual void OnCollision(Collider* collider);
};

