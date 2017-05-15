#pragma once
#include "Enemy.h"
class EnemyMortar :
	public Enemy
{
public:
	EnemyMortar(int x, int y, int angle, int sub_type);
	~EnemyMortar();
	virtual void Move();

private:

	Animation mortar;

	int current_angle;

	bool disappear = false;
	int timer;
	int direction;
	iPoint shooting_position;

};

