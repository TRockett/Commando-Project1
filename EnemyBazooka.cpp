#include "EnemyBazooka.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "SDL/include/SDL_timer.h"
#include <math.h>
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleSceneGame.h"


EnemyBazooka::EnemyBazooka(int x, int y, int angle, int sub_type, int isglobal) : Enemy(x, y, angle, sub_type,isglobal)
{
	current_angle = angle;

	collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY, App->enemies);

	movement.loop = false;
	movement.PushBack({ sinf((float)current_angle), cosf((float)current_angle) }, 0);

	e1_forward.PushBack({ 207,129,16,26 });
	e1_forward.PushBack({ 223,129,16,26 });
	e1_forward.speed = 0.15f;
	e1_forward.loop = true;


	e1_down_left.PushBack({ 241,129,16,22 });
	e1_down_left.PushBack({ 260,129,15,22 });
	e1_down_left.PushBack({ 278,129,15,21 });
	e1_down_left.speed = 0.15f;
	e1_down_left.loop = false;

	e1_down_right.PushBack({ 241,129,16,22 });
	e1_down_right.PushBack({ 260,129,15,22 });
	e1_down_right.PushBack({ 294,131,15,20 });	
	e1_down_right.speed = 0.15f;
	e1_down_right.loop = false;

	e1_backward.PushBack({ 241,129,16,22 });
	e1_backward.PushBack({ 260,129,15,22 });
	e1_backward.speed = 0.15f;
	e1_backward.loop = false;

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
	shoot = false;
}


EnemyBazooka::~EnemyBazooka()
{
}

void EnemyBazooka::Move()
{
	position = initial_position + movement.GetCurrentPosition();
	iPoint player_pos = App->player->GetPosition();
	prev_position = position;


	if (this->position.y >= App->player->position.y + (SCREEN_HEIGHT / 2) + 30 || this->position.x <= 0 - 30 || this->position.x >= (SCREEN_WIDTH)+30)
	{
		this->disappear = true;
	}

	if ((movement.Finished() || collision == true) && dead == false && dying == false)
	{
		movement.Clear();
		movement.Reset();

		if (collision == true)
		{
			position = prev_position;
			current_angle = Collisionangle(current_angle);
			shoot = false;
		}

		if (shoot == false)
		{
			animation = &e1_forward;
			movement.PushBack({ sinf((float)current_angle * (M_PI / 180.0f)), cosf((float)current_angle * (M_PI / 180.0f)) }, 50);
			throwing.Reset();
			shoot = true;
		}
		else
		{
			movement.PushBack({ 0 , 0 }, 30);
			float deltaX = -position.x + player_pos.x;
			float deltaY = -position.y + player_pos.y;
			float angle = atan2f(deltaY, deltaX);
			float vec_mod = sqrtf(pow(deltaX, 2) + pow(deltaY, 2));
			fPoint normalised_v = { deltaX / vec_mod, deltaY / vec_mod };
			if (position.x > player_pos.x - 20)
			{
				shooting_position.x = 0;
				shooting_position.y = 18;
				animation = &e1_down_left;
				if (animation->Finished() == true)
				{
					App->particles->Missile_downleft.speed = { (float)(normalised_v.x * 2.0f), (float)((normalised_v.y * 2.0f)) };
					App->particles->AddParticle(App->particles->Bluefire_downleft, position.x + shooting_position.x, position.y + shooting_position.y, MISSILE, COLLIDER_ENEMY_SHOT, nullptr, 0, false);
					App->particles->AddParticle(App->particles->Missile_downleft, position.x + shooting_position.x, position.y + shooting_position.y, MISSILE, COLLIDER_ENEMY_SHOT, nullptr, 0, false);
					animation->Reset();
					shoot = false;
				}
			}
			else if (position.x < player_pos.x + 20)
			{
				shooting_position.x = 19;
				shooting_position.y = 18;
				animation = &e1_down_right;
				if (animation->Finished() == true)
				{
					App->particles->Missile_downright.speed = { (float)(normalised_v.x * 2.0f), (float)((normalised_v.y * 2.0f)) };
					App->particles->AddParticle(App->particles->Bluefire_downright, position.x + shooting_position.x, position.y + shooting_position.y, MISSILE, COLLIDER_ENEMY_SHOT, nullptr, 0, false);
					App->particles->AddParticle(App->particles->Missile_downright, position.x + shooting_position.x, position.y + shooting_position.y, MISSILE, COLLIDER_ENEMY_SHOT, nullptr, 0, false);
					animation->Reset();
					shoot = false;
				}
			}
			else
			{
				shooting_position.x = 4;
				shooting_position.y = 19;
				animation = &e1_backward;
				if (animation->Finished() == true)
				{
					App->particles->Missile_down.speed = { (float)(normalised_v.x * 2.0f), (float)((normalised_v.y * 2.0f)) };
					App->particles->AddParticle(App->particles->Bluefire_down, position.x + shooting_position.x, position.y + shooting_position.y, MISSILE, COLLIDER_ENEMY_SHOT, nullptr, 0, false);
					App->particles->AddParticle(App->particles->Missile_down, position.x + shooting_position.x, position.y + shooting_position.y, MISSILE, COLLIDER_ENEMY_SHOT, nullptr, 0, false);
					animation->Reset();
					shoot = false;
				}
			}

		}
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
