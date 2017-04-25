#pragma once
#include "Enemy.h"
class EnemyGrenade :
	public Enemy
{
public:
	EnemyGrenade(int x, int y);
	virtual ~EnemyGrenade();
};

