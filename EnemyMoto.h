#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Path.h"

class EnemyMoto :
	public Enemy
{
private:
	Path movement;

	Animation riding;
	Animation throwing_grenade;
public:
	
	EnemyMoto(int x, int y);
	void Move();
	virtual ~EnemyMoto();
};

