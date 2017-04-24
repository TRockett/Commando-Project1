#pragma once
#include "Enemy.h"
#include "Animation.h"

class EnemyJump :
	public Enemy
{


private: 
	Animation jump;
public:
	EnemyJump(int x, int y);
	virtual ~EnemyJump();
};

