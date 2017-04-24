#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Path.h"
class Enemywprisoner :
	public Enemy
{

private:
	Path movement;
	Animation walking;

public:

	Enemywprisoner(int x, int y);
	virtual ~Enemywprisoner();
	/*void Enemywprisoner::Move();*/

};

