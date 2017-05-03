#include "EnemyGrenade.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "SDL/include/SDL_timer.h"
#include <math.h>
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleSceneGame.h"



EnemyGrenade::EnemyGrenade(int x, int y , int angle, int sub_type) : Enemy (x,y, angle, sub_type)
{// walk forward animation (arcade sprite sheet)

	e1_forward.PushBack({ 0 + 151, 209, 13, 23 });
	e1_forward.PushBack({ 31 + 151, 210, 13, 23 });
	e1_forward.PushBack({ 17 + 151, 209, 13, 23 });
	e1_forward.PushBack({ 31 + 151, 210, 13, 23 });
	e1_forward.loop = true;
	e1_forward.speed = 0.15f;

	//walk diagonal down-right

	e1_down_right.PushBack({ 49 + 151,258,15,23 });
	e1_down_right.PushBack({ 66 + 151,259,15,23 });
	e1_down_right.PushBack({ 82 + 151,257,15,22 });
	e1_down_right.PushBack({ 66 + 151,259,15,23 });
	e1_down_right.speed = 0.15f;
	e1_down_right.loop = true;

	//walk diagonal down-left

	e1_down_left.PushBack({ 0 + 151,257,15,22 });
	e1_down_left.PushBack({ 16 + 151,258,15,23 });
	e1_down_left.PushBack({ 33 + 151,257,15,23 });
	e1_down_left.PushBack({ 16 + 151,258,15,23 });
	e1_down_left.speed = 0.15f;
	e1_down_left.loop = true;

	//walk diagonal up-left enemy

	e1_up_left.PushBack({ 16 + 151,282,16,23 });
	e1_up_left.PushBack({ 0 + 151,282,15,23 });
	e1_up_left.PushBack({ 32 + 151,282,16,22 });
	e1_up_left.PushBack({ 0 + 151,282,15,23 });
	e1_up_left.speed = 0.15f;
	e1_up_left.loop = true;

	//walk diagonal up-right

	e1_up_right.PushBack({ 49 + 151,282,16,22 });
	e1_up_right.PushBack({ 82 + 151,282,15,23 });
	e1_up_right.PushBack({ 65 + 151,282,16,23 });
	e1_up_right.PushBack({ 82 + 151,282,15,23 });
	e1_up_right.speed = 0.15f;
	e1_up_right.loop = true;

	//walk right animation enemyy


	e1_right.PushBack({ 0 + 151,306,16,24 });
	e1_right.PushBack({ 17 + 151,306,18,22 }, { 2,0 });
	e1_right.PushBack({ 0 + 151,306,16,24 });
	e1_right.PushBack({ 36 + 151,306,16,22 }, { 2,0 });

	e1_right.loop = true;
	e1_right.speed = 0.15f;


	//walk left annimation enemy

	e1_left.PushBack({ 53 + 151,306,15,22 }, { 7,0 });
	e1_left.PushBack({ 88 + 151,306,16,24 }, { 7,0 });
	e1_left.PushBack({ 69 + 151,306,18,22 }, { 7,0 });
	e1_left.PushBack({ 88 + 151,306,16,24 }, { 7,0 });
	e1_left.loop = true;
	e1_left.speed = 0.15f;

	//walk backward animation emey
	e1_backward.PushBack({ 0 + 151, 331, 12, 22 });
	e1_backward.PushBack({ 12 + 151, 331, 13, 22 });
	e1_backward.PushBack({ 25 + 151, 331, 13, 22 });
	e1_backward.PushBack({ 12 + 151, 331, 13, 22 });
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



	animation = &e1_forward;
	current_angle = angle;

};


EnemyGrenade::~EnemyGrenade()
{
}

void EnemyGrenade::Move()
{
	iPoint player_pos = App->player->GetPosition();
	if (SDL_GetTicks() >= timer + 1000)
	{
		float deltaX = -position.x + player_pos.x;
		float deltaY = -position.y + player_pos.y;
		float angle = atan2f(deltaY, deltaX);
		float vec_mod = sqrtf(pow(deltaX, 2) + pow(deltaY, 2));
		fPoint normalised_v = { deltaX / vec_mod, deltaY / vec_mod };

		App->particles->bullet.speed = { (float)(normalised_v.x * 1.0f), (float)(normalised_v.y * 1.0f) };
		App->particles->bullet.life = 1800;
		App->particles->AddParticle(App->particles->bullet, position.x + shooting_position.x, position.y + shooting_position.y, BULLET_ENEMY, COLLIDER_ENEMY_SHOT);
		timer = SDL_GetTicks();
	}
	if (this->position.y >= App->player->position.y + (SCREEN_HEIGHT / 2) + 30 || this->position.x <= 0 - 30 || this->position.x >= (SCREEN_WIDTH)+30)
	{
		this->disappear = true;
	}

	if ((collision == true)&& dead == false && dying == false)
	{
		movement.Clear();
		movement.Reset();
		if (collision != true)
		{
			current_angle = (rand() % 8) * 45;
		}
		else
		{
			position = prev_position;
			current_angle = -Collisionangle(this->collider, collider);

		}

		animation = GetAnimationForDirection(current_angle);
		movement.PushBack({ sinf((float)current_angle), cosf((float)current_angle) }, 50);
		collision = false;
	}
	else if (dying == true)
	{
		animation = &death;
		collider->active = false;
		movement.Clear();
		movement.Reset();

		if (animation->Finished() == true)
		{
			dead = true;
			App->scene_game->score = App->scene_game->score + 200;
			App->scene_game->screen_enemies--;
			App->enemies->EraseEnemy(this);
		}
	}

	else if (disappear == true)
	{
		animation = &death;
		collider->active = false;
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
		
void EnemyGrenade::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_WALL || collider->type == COLLIDER_WATER)
	{
		collision = true;

	}
	if (collider->type == COLLIDER_PLAYER_SHOT)
	{
		dying = true;
	}

}

