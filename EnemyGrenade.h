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
	bool disappear = false;
	int timer;
	int direction;
	iPoint shooting_position;
	bool throwi;
	float grenadeac;
public:
	EnemyGrenade(int x, int y, int angle, int sub_type);
	virtual ~EnemyGrenade();

	virtual void Move();




};

