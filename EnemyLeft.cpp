#include "EnemyLeft.h"




EnemyLeft::EnemyLeft(int x, int y) : Enemy(x, y)
{
	e1_forward.PushBack({ 0, 220, 15, 23 });
	e1_forward.PushBack({ 16, 220, 15, 22 });
	e1_forward.PushBack({ 36, 220, 15, 23 });
	e1_forward.loop = true;
	e1_forward.speed = 0.15f;



	movement.PushBack({ 0.7f, -0.5f }, 65, animation);
}


EnemyLeft::~EnemyLeft()
{
}

void EnemyLeft::Move() {
	this->position = movement.GetCurrentPosition();
}