#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Path.h"

class Commander :
	public Enemy
{
public:
	Commander(int x, int y, int angle, int sub_type);
	~Commander();

	virtual void Move();

private:
	Path movement;

	int current_angle;
	bool disappear = false;
	int timer;
	int direction;
	iPoint shooting_position;
};

