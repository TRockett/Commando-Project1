#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Path.h"

class EnemyGrenade :
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

	int current_angle;
	bool collision = false;
	bool dying = false;
	bool disappear = false;
	int timer;
	int direction;
	iPoint shooting_position;

public:
	EnemyGrenade(int x, int y, int angle, int sub_type);
	virtual ~EnemyGrenade();

	virtual void Move();
	virtual void OnCollision(Collider* collider);

	/*void EnemyGrenade::Move();*/

};

