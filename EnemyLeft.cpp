#include "EnemyLeft.h"
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleSceneGame.h"


EnemyLeft::EnemyLeft(int x, int y) : Enemy(x, y)
{

	// walk forward animation (arcade sprite sheet)

	e1_forward.PushBack({ 30, 209, 13, 23 });
	e1_forward.PushBack({ 0, 209, 13, 23 });
	e1_forward.PushBack({ 30, 209, 13, 23 });
	e1_forward.PushBack({ 17, 209, 13, 23 });

	e1_forward.loop = true;
	e1_forward.speed = 0.15f;

	//walk diagonal down-left

	e1_down_left.PushBack({ 18,258,13,23 });
	e1_down_left.PushBack({ 0,257,15,22 });
	e1_down_left.PushBack({ 18,258,13,23 });
	e1_down_left.PushBack({ 32,258,15,23 });
	e1_down_left.speed = 0.15f;
	e1_down_left.loop = true;

	//walk diagonal down-right

	e1_down_right.PushBack({ 66,259,13,23 });
	e1_down_right.PushBack({ 49,258,15,22 });
	e1_down_right.PushBack({ 66,259,13,23 });
	e1_down_right.PushBack({ 81,258,15,23 });
	e1_down_right.speed = 0.15f;
	e1_down_right.loop = true;

	//walk diagonal up-right enemy

	e1_up_right.PushBack({ 0,282,15,23 });
	e1_up_right.PushBack({ 16,282,16,23 });
	e1_up_right.PushBack({ 0,282,15,23 });
	e1_up_right.PushBack({ 32,282,16,22 });
	e1_up_right.speed = 0.15f;
	e1_up_right.loop = true;

	//walk diagonal up-left

	e1_up_left.PushBack({ 81,281,15,23 });
	e1_up_left.PushBack({ 65,282,16,23 });
	e1_up_left.PushBack({ 81,281,15,23 });
	e1_up_left.PushBack({ 49,282,16,22 });
	e1_up_left.speed = 0.15f;
	e1_up_left.loop = true;

	//walk right animation enemyy


	e1_left.PushBack({ 0,306,16,24 });
	e1_left.PushBack({ 17,306,18,22 }, { 2,0 });
	e1_left.PushBack({ 0,306,16,24 });
	e1_right.PushBack({ 36,306,16,22 }, { 2,0 });

	e1_right.loop = true;
	e1_right.speed = 0.15f;


	//walk left annimation enemy


	e1_left.PushBack({ 88,306,16,24 }, { 7,0 });
	e1_left.PushBack({ 69,306,18,22 }, { 7,0 });
	e1_left.PushBack({ 88,306,16,24 }, { 7,0 });
	e1_left.PushBack({ 53,306,15,22 }, { 7,0 });
	e1_left.loop = true;
	e1_left.speed = 0.15f;

	//walk backward animation emey

	e1_backward.PushBack({ 12, 331, 13, 22 });
	e1_backward.PushBack({ 0, 331, 12, 22 });
	e1_backward.PushBack({ 12, 331, 13, 22 });
	e1_backward.PushBack({ 15, 331, 13, 22 });
	e1_backward.loop = true;
	e1_backward.speed = 0.15f;

	//death
	death.PushBack({0, 459, 15, 14});

	death.PushBack({ 17, 449, 23, 26 });
	death.PushBack({ 0, 459, 15, 14 });
	death.PushBack({ 17, 449, 23, 26 });
	death.PushBack({ 0, 459, 15, 14 });
	death.PushBack({ 17, 449, 23, 26 });
	death.PushBack({ 0, 459, 15, 14 });
	death.PushBack({ 17, 449, 23, 26 });

	death.PushBack({ 0, 459, 15, 14 });
	death.PushBack({ 43, 449, 23, 26 });
	death.PushBack({ 0, 459, 15, 14 });
	death.PushBack({ 43, 449, 23, 26 });
	death.PushBack({ 0, 459, 15, 14 });
	death.PushBack({ 43, 449, 23, 26 });
	death.PushBack({ 0, 459, 15, 14 });
	death.PushBack({ 43, 449, 23, 26 });
	death.PushBack({ 0, 459, 15, 14 });
	death.loop = false;
	death.speed = 0.5f;

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
	prev_position = position;
	if (movement.Finished()||collision == true)
	{
		movement.Clear();
		movement.Reset();
		int angle = (rand() % 8) * 45;
		animation = GetAnimationForDirection(angle);
		movement.PushBack({ sinf((float)angle), cosf((float)angle) }, 100);
		collision = false;

		
	}
}

Animation* EnemyLeft::GetAnimationForDirection(int dir) {
	Animation* animation = nullptr;
	switch (dir) {
	case 0:
		animation = &e1_forward;
		break;
	case 45:
		animation = &e1_up_right;
		break;
	case 90:
		animation = &e1_right;
		break;
	case 135:
		animation = &e1_down_right;
		break;
	case 180:
		animation = &e1_backward;
		break;
	case 225:
		animation = &e1_down_left;
		break;
	case 270:
		animation = &e1_left;
		break;
	case 315:
		animation = &e1_up_left;
		break;
	}
	return animation;
}
	void EnemyLeft::OnCollision(Collider* collider)
	{
		if (collider->type == COLLIDER_WALL ||  collider->type == COLLIDER_WATER)
		{
			collision = true;
			prev_position;
		}
		if (collider->type == COLLIDER_PLAYER_SHOT || collider->type == EXPLOSION)
		{
			delete this;
			App->scene_game->screen_enemies--;
		}
	}

