#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Path.h"

class EnemyGrenade :
	public Enemy
{
private:
	Path movement;

	int current_angle;
	bool collision = false;
	bool dying = false;
	bool disappear = false;
	int timer;
	int direction;
	iPoint shooting_position;
	bool throwi;

public:
	EnemyGrenade(int x, int y, int angle, int sub_type);
	virtual ~EnemyGrenade();

	virtual void Move();



};

