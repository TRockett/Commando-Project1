#include "EnemyLeft.h"
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"



EnemyLeft::EnemyLeft(int x, int y) : Enemy(x, y)
{

	// walk forward animation (arcade sprite sheet)

	e1_forward.PushBack({ 0, 220, 15, 23 });
	e1_forward.PushBack({ 16, 220, 15, 22 });
	e1_forward.PushBack({ 36, 220, 15, 23 });
	e1_forward.loop = true;
	e1_forward.speed = 0.15f;

	//walk diagonal down-left

	e1_down_left.PushBack({ 105,24,15,22 });
	e1_down_left.PushBack({ 120,24,15,22 });
	e1_down_left.PushBack({ 105,24,15,22 });
	e1_down_left.PushBack({ 137,24,15,22 });
	e1_down_left.loop = true;
	e1_down_left.speed = 0.15f;

	//walk diagonal down-right

	e1_down_right.PushBack({ 88,23,15,22 });
	e1_down_right.PushBack({ 56,23,15,22 });
	e1_down_right.PushBack({ 88,23,15,22 });
	e1_down_right.PushBack({ 73,23,15,22 });
	e1_down_right.loop = true;
	e1_down_right.speed = 0.15f;

	//walk diagonal up-right enemy

	e1_up_right.PushBack({ 0,246,17,22 });
	e1_up_right.PushBack({ 19,246,15,22 }, { 2,0 });
	e1_up_right.PushBack({ 44,246,16,21 });
	e1_up_right.PushBack({ 19,246,15,22 }, { 7,0 });
	e1_up_right.loop = true;
	e1_up_right.speed = 0.15f;

	//walk diagonal down-left

	e1_up_left.PushBack({ 97,47,15,22 });
	e1_up_left.PushBack({ 56,47,18,21 });
	e1_up_left.PushBack({ 97,47,15,22 });
	e1_up_left.PushBack({ 75,47,21,21 });
	e1_up_left.loop = true;
	e1_up_left.speed = 0.15f;

	//walk right animation enemyy


	e1_right.PushBack({ 78,246,16,22 });
	e1_right.PushBack({ 98,246,15,22 }, { 4,0 });
	e1_right.PushBack({ 78,246,16,22 });
	e1_right.PushBack({ 118,246,16,21 }, { 2,0 });

	e1_right.loop = true;
	e1_right.speed = 0.15f;


	//walk left annimation enemy

	e1_left.PushBack({ 0,246,17,22 });
	e1_left.PushBack({ 19,246,15,22 }, { 2,0 });
	e1_left.PushBack({ 44,246,16,21 });
	e1_left.PushBack({ 19,246,15,22 }, { 7,0 });
	e1_left.loop = true;
	e1_left.speed = 0.15f;

	//walk backward animation emey

	e1_backward.PushBack({ 0, 220, 15, 23 });
	e1_backward.PushBack({ 16, 220, 15, 22 });
	e1_backward.PushBack({ 36, 220, 15, 23 });
	e1_backward.loop = true;
	e1_backward.speed = 0.15f;

	collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY, App->enemies);


	movement.PushBack({ 0.0f, 0.1f }, 100, animation);
	movement.PushBack({ 0.0f, -0.1f }, 100, animation);
	movement.loop = false;

	animation = &e1_forward;
}


EnemyLeft::~EnemyLeft()
{
}

void EnemyLeft::Move() {
	position = initial_position + movement.GetCurrentPosition();
	if (movement.Finished())
	{
		movement.Clear();
		movement.Reset();
		int random = (rand() % 8) * 45 * (M_PI / 180.0f);
		movement.PushBack({ sinf((float)random), cosf((float)random) }, 100);
	}
}

Animation* EnemyLeft::GetAnimationForDirection(int dir) {
	switch (dir) {
	case 0:
		break;
	case 45:
		break;
	case 90:
		break;
	case 135:
		break;
	case 180:
		break;
	case 225:
		break;
	case 270:
		break;
	case 315:
		return 0;
	}
}