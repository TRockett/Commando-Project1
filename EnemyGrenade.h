#pragma once
#include "Enemy.h"
#include "Animation.h"

class EnemyGrenade :
	public Enemy
{
private:
	Animation e1_forward;
	Animation e1_backward;
	Animation e1_left;
	Animation e1_right;
	Animation e1_up_right;
	Animation e1_up_left;
	Animation e1_down_right;
	Animation e1_down_left;
	Animation death;
public:
	EnemyGrenade(int x, int y);
	virtual ~EnemyGrenade();
};

