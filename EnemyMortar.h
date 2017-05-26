#pragma once
#include "Enemy.h"
class EnemyMortar :
	public Enemy
{
public:
	EnemyMortar(int x, int y, int angle, int sub_type, int isglobal);
	~EnemyMortar();
	virtual void Move();

private:
	iPoint level_dimensions;

	Animation mortar;

	Animation mortar_left1;
	Animation mortar_left2;
	Animation mortar_left3;
	Animation mortar_left4;

	Animation mortar_right1;
	Animation mortar_right2;
	Animation mortar_right3;
	Animation mortar_right4;

	int current_angle;

	bool disappear = false;
	int timer;
	int direction;
	iPoint shooting_position;

};

