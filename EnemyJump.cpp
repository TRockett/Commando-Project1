#include "EnemyJump.h"
#include "EnemyLeft.h"
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleSceneGame.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"



EnemyJump::EnemyJump(int x, int y) : Enemy(x,y)
{
	//walking before jump

	walk.PushBack({703, 558, 16, 23});
	walk.PushBack({ 724, 558, 18, 21 });
	walk.PushBack({ 703, 556, 16, 23 });
	walk.PushBack({ 746, 556, 16, 22 });
	walk.loop = true;
	walk.speed = 0.2f;

	//jump animation
	jump.PushBack({705, 583, 16, 19});
	jump.PushBack({ 725, 583, 16, 22 });
	jump.PushBack({ 744, 583, 22, 21 });
	jump.PushBack({ 768, 583, 23, 23 });
	jump.PushBack({ 705, 583, 16, 19 });

	jump.loop = false;
	jump.speed = 0.1f;

	// walk forward animation (arcade sprite sheet)

	e1_forward.PushBack({ 0, 209, 13, 23 });
	e1_forward.PushBack({ 31, 210, 13, 23 });
	e1_forward.PushBack({ 17, 209, 13, 23 });
	e1_forward.PushBack({ 31, 210, 13, 23 });
	e1_forward.loop = true;
	e1_forward.speed = 0.15f;

	//walk diagonal down-right

	e1_down_right.PushBack({ 49,258,15,23 });
	e1_down_right.PushBack({ 66,259,15,23 });
	e1_down_right.PushBack({ 82,257,15,22 });
	e1_down_right.PushBack({ 66,259,15,23 });
	e1_down_right.speed = 0.15f;
	e1_down_right.loop = true;

	//walk diagonal down-left

	e1_down_left.PushBack({ 0,257,15,22 });
	e1_down_left.PushBack({ 16,258,15,23 });
	e1_down_left.PushBack({ 33,257,15,23 });
	e1_down_left.PushBack({ 16,258,15,23 });
	e1_down_left.speed = 0.15f;
	e1_down_left.loop = true;

	//walk diagonal up-left enemy

	e1_up_left.PushBack({ 16,282,16,23 });
	e1_up_left.PushBack({ 0,282,15,23 });
	e1_up_left.PushBack({ 32,282,16,22 });
	e1_up_left.PushBack({ 0,282,15,23 });
	e1_up_left.speed = 0.15f;
	e1_up_left.loop = true;

	//walk diagonal up-right

	e1_up_right.PushBack({ 49,282,16,22 });
	e1_up_right.PushBack({ 82,282,15,23 });
	e1_up_right.PushBack({ 65,282,16,23 });
	e1_up_right.PushBack({ 82,282,15,23 });
	e1_up_right.speed = 0.15f;
	e1_up_right.loop = true;

	//walk right animation enemyy


	e1_right.PushBack({ 0,306,16,24 });
	e1_right.PushBack({ 17,306,18,22 }, { 2,0 });
	e1_right.PushBack({ 0,306,16,24 });
	e1_right.PushBack({ 36,306,16,22 }, { 2,0 });

	e1_right.loop = true;
	e1_right.speed = 0.15f;


	//walk left annimation enemy

	e1_left.PushBack({ 53,306,15,22 }, { 7,0 });
	e1_left.PushBack({ 88,306,16,24 }, { 7,0 });
	e1_left.PushBack({ 69,306,18,22 }, { 7,0 });
	e1_left.PushBack({ 88,306,16,24 }, { 7,0 });
	e1_left.loop = true;
	e1_left.speed = 0.15f;

	//walk backward animation emey
	e1_backward.PushBack({ 0, 331, 12, 22 });
	e1_backward.PushBack({ 12, 331, 13, 22 });
	e1_backward.PushBack({ 25, 331, 13, 22 });
	e1_backward.PushBack({ 12, 331, 13, 22 });
	e1_backward.loop = true;
	e1_backward.speed = 0.15f;

	//death
	death.PushBack({ 0, 459, 15, 14 });

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


	/*movement.PushBack({ 0.0f, 0.1f }, 100, animation);
	movement.PushBack({ 0.0f, -0.1f }, 100, animation);*/
	movement.loop = false;

	animation = &e1_forward;
	angle = (rand() % 8) * 45;
	timer = SDL_GetTicks();

	if (position.x < SCREEN_WIDTH / 2)
	{
		dir = 1;
	}
	else
	{
		dir = -1;
	}

};


EnemyJump::~EnemyJump()
{
}



void EnemyJump::Move() {


	position = initial_position + movement.GetCurrentPosition();
	prev_position = position;
	iPoint player_pos = App->player->GetPosition();
	if (App->player->position.y - SCREEN_HEIGHT / 2 <= position.y)
	{
		if (jump_int == true)
		{
			animation = &walk;

			if (jump_state == 0)
			{
				movement.PushBack({ 0,0 }, 200);
				if (movement.Finished() == true)
				{
					jump_state = 1;
				}
			}
			else if (jump_state == 1)
			{
				movement.PushBack({ dir * 0.3f,0 }, 150);
				if (movement.Finished() == true)
				{
					jump_state = 2;
				}
			}
			else if (jump_state == 2)
			{
				animation = &jump;
				movement.PushBack({ dir * 0.5f, jump_speed }, 200);
				jump_speed += 0.2f;
				if (movement.Finished() == true)
				{
					jump_int = false;
				}
			}
		}
	}

	else
	{		

		if (SDL_GetTicks() >= timer + 1000)
		{
			float deltaX = -position.x + player_pos.x;
			float deltaY = -position.y + player_pos.y;
			float angle = atan2f(deltaY, deltaX);

			App->particles->bullet.speed = { (float)(deltaX * 0.015f /** cosf(angle)*/), (float)(deltaY * 0.015f /** sinf(angle)*/) };
			App->particles->AddParticle(App->particles->bullet, position.x, position.y, BULLET_ENEMY, COLLIDER_ENEMY_SHOT);
			timer = SDL_GetTicks();
		}

		if ((movement.Finished() || collision == true) && dead == false && dying == false)
		{
			movement.Clear();
			movement.Reset();
			if (collision != true)
			{
				int angle = (rand() % 8) * 45;
			}

			animation = GetAnimationForDirection(angle);
			movement.PushBack({ sinf((float)angle), cosf((float)angle) }, 100);
			collision = false;
		}
		else if (dying == true)
		{
			animation = &death;
			App->collision->EraseCollider(this->collider);
			movement.Clear();
			movement.Reset();

			if (animation->Finished() == true)
			{
				dead = true;
				App->scene_game->screen_enemies--;
				App->enemies->EraseEnemy(this);
			}
		}
	}
}

Animation* EnemyJump::GetAnimationForDirection(int dir) {
	Animation* animation = nullptr;
	switch (dir) {
	case 0:
		animation = &e1_forward;
		break;
	case 45:
		animation = &e1_up_left;
		break;
	case 90:
		animation = &e1_right;
		break;
	case 135:
		animation = &e1_down_left;
		break;
	case 180:
		animation = &e1_backward;
		break;
	case 225:
		animation = &e1_down_right;
		break;
	case 270:
		animation = &e1_left;
		break;
	case 315:
		animation = &e1_up_right;
		break;
	}
	return animation;
}
void EnemyJump::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_WALL || collider->type == COLLIDER_WATER)
	{
		collision = true;
		angle = -Collisionangle(this->collider, collider);
		prev_position = position;
	}
	if (collider->type == COLLIDER_PLAYER_SHOT || collider->type == EXPLOSION || collider->type == COLLIDER_MAX)
	{
		dying = true;
	}

}

