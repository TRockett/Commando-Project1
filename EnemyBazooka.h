#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Path.h"

class EnemyBazooka :
	public Enemy
{
public:
	EnemyBazooka(int x, int y, int angle, int sub_type);
	~EnemyBazooka();

	virtual void Move();

private:
	Path movement;

	int current_angle;
	bool disappear = false;
	bool shoot;
	int timer;
	int direction;
	iPoint shooting_position;
};

