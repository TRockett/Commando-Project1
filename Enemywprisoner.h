#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Path.h"
class Enemywprisoner :
	public Enemy
{

private:
	//soldier left

	Animation walk;
	Animation death;

	//soldier right

	Animation walk_2;
	Animation death_2;

	//prisoner

	Animation walk_3;
	Animation free;
	Animation free_d;


	Path movement;
	Animation walking;
	bool dying;
	int alive;

public:

	Enemywprisoner(int x, int y, int angle, int sub_type);
	virtual ~Enemywprisoner();
	void Enemywprisoner::Move();

};

