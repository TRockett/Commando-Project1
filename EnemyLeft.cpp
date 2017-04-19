#include "EnemyLeft.h"
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"



EnemyLeft::EnemyLeft(int x, int y) : Enemy(x, y)
{
	e1_forward.PushBack({ 0, 220, 15, 23 });
	e1_forward.PushBack({ 16, 220, 15, 22 });
	e1_forward.PushBack({ 36, 220, 15, 23 });
	e1_forward.loop = true;
	e1_forward.speed = 0.15f;

	collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY, App->enemies);


	movement.PushBack({0.5f, 0.6f }, 65, animation);
}


EnemyLeft::~EnemyLeft()
{
}

void EnemyLeft::Move() {
	animation = &App->enemies->e1_forward;
	position += movement.GetCurrentPosition();
}