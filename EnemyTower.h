#pragma once
#include "Enemy.h"
class EnemyTower :
	public Enemy
{
public:
	EnemyTower(int x, int y, int angle, int sub_type);
	~EnemyTower();
	virtual void Move();
private:
	Animation anim1;
	Animation anim2;
	Animation anim3;
	Animation anim4;

	int timer;

};

