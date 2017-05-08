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

	e1_down_right.PushBack({ 49 + 148,258,15,23 });
	e1_down_right.PushBack({ 66 + 148,259,15,23 });
	e1_down_right.PushBack({ 82 + 148,257,15,22 });
	e1_down_right.PushBack({ 66 + 148,259,15,23 });
	e1_down_right.speed = 0.15f;
	e1_down_right.loop = true;

	//walk diagonal down-left

	e1_down_left.PushBack({ 0 + 148,257,15,22 });
	e1_down_left.PushBack({ 16 + 148,258,15,23 });
	e1_down_left.PushBack({ 33 + 148,257,15,23 });
	e1_down_left.PushBack({ 16 + 148,258,15,23 });
	e1_down_left.speed = 0.15f;
	e1_down_left.loop = true;

	//walk diagonal up-left enemy

	e1_up_left.PushBack({ 16 + 148,282,16,23 });
	e1_up_left.PushBack({ 0 + 148,282,15,23 });
	e1_up_left.PushBack({ 32 + 148,282,16,22 });
	e1_up_left.PushBack({ 0 + 148,282,15,23 });
	e1_up_left.speed = 0.15f;
	e1_up_left.loop = true;

	//walk diagonal up-right

	e1_up_right.PushBack({ 49 + 148,282,16,24 });
	e1_up_right.PushBack({ 82 + 148,282,18,22 });
	e1_up_right.PushBack({ 65 + 148,282,16,24 });
	e1_up_right.PushBack({ 82 + 148,282,16,22 });
	e1_up_right.speed = 0.15f;
	e1_up_right.loop = true;

	//walk right animation enemyy


	e1_right.PushBack({ 148,306,16,24 });
	e1_right.PushBack({ 164,306,18,22 }, { 2,0 });
	e1_right.PushBack({ 148,306,16,24 });
	e1_right.PushBack({ 183,306,16,22 }, { 2,0 });

	e1_right.loop = true;
	e1_right.speed = 0.15f;


	//walk left annimation enemy

	e1_left.PushBack({ 53 + 148,306,15,22 }, { 7,0 });
	e1_left.PushBack({ 88 + 148,306,16,24 }, { 7,0 });
	e1_left.PushBack({ 69 + 148,306,18,22 }, { 7,0 });
	e1_left.PushBack({ 88 + 148,306,16,24 }, { 7,0 });
	e1_left.loop = true;
	e1_left.speed = 0.15f;

	//walk backward animation emey
	e1_backward.PushBack({ 0 + 148, 331, 12, 22 });
	e1_backward.PushBack({ 12 + 148, 331, 13, 22 });
	e1_backward.PushBack({ 25 + 148, 331, 13, 22 });
	e1_backward.PushBack({ 12 + 148, 331, 13, 22 });
	e1_backward.loop = true;
	e1_backward.speed = 0.15f;

	//grenade throwing
	throwing.PushBack({ 200,330,20,24 });
	throwing.PushBack({ 223,331,15,24 });
	throwing.PushBack({ 241,332,15,22 });
	throwing.loop = false;
	throwing.speed = 0.1f;

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

	current_angle = angle;

	collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY, App->enemies);

	movement.loop = false;
	movement.PushBack({ sinf((float)current_angle *(M_PI / 180.0f)), cosf((float)current_angle *(M_PI / 180.0f)) }, 0);

	animation = &e1_forward;
	
	throwi = false;


};


EnemyGrenade::~EnemyGrenade()
{
}

void EnemyGrenade::Move()
{
	position = initial_position + movement.GetCurrentPosition();
	iPoint player_pos = App->player->GetPosition();
	prev_position = position;
	grenadeac = grenadeac + 0.1f;

	if (this->position.y >= App->player->position.y + (SCREEN_HEIGHT / 2) + 30 || this->position.x <= 0 - 30 || this->position.x >= (SCREEN_WIDTH)+30)
	{
		this->disappear = true;
	}

	if ((movement.Finished() || collision == true) && dead == false && dying == false)
	{
		movement.Clear();
		movement.Reset();

		if (sub_type == 1)
		{
			if (collision == true)
			{
				position = prev_position;
				current_angle = Collisionangle(this->collider, collider);
			}
			else if (throwi == false)
			{
				animation = GetAnimationForDirection(current_angle);
				movement.PushBack({ sinf((float)current_angle), cosf((float)current_angle) }, 50);
				throwing.Reset();
				
			}
			else
			{
				animation = &throwing;
				movement.PushBack({ 0 , 0 }, 30);
				float deltaX = -position.x + player_pos.x;
				float deltaY = -position.y + player_pos.y;
				float angle = atan2f(deltaY, deltaX);
				float vec_mod = sqrtf(pow(deltaX, 2) + pow(deltaY, 2));
				fPoint normalised_v = { deltaX / vec_mod, deltaY / vec_mod };

				App->particles->grenade.speed = { (float)(normalised_v.x * 1.0f), (float)((normalised_v.y * 1.0f)) };
				App->particles->AddParticle(App->particles->grenade, position.x + shooting_position.x, position.y + shooting_position.y, GRENADE_ENEMY, COLLIDER_NONE,nullptr,0,true);

			}
			
			collision = false;
			throwi = !throwi;

		}
		else if (sub_type == 2)
		{
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
		}
		

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




