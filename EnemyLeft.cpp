#include "EnemyLeft.h"
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleSceneGame.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"

EnemyLeft::EnemyLeft(int x, int y, int angle, int sub_type) : Enemy(x, y, angle, sub_type)
{

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

	e1_down_left.PushBack({0,257,15,22 });
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

	//walk right 
	walk.PushBack({ 703, 558, 16, 23 });
	walk.PushBack({ 724, 558, 18, 21 });
	walk.PushBack({ 703, 556, 16, 23 });
	walk.PushBack({ 746, 556, 16, 22 });
	walk.loop = true;
	walk.speed = 0.2f;

	//jump right animation
	jump.PushBack({ 705, 583, 16, 19 });
	jump.PushBack({ 725, 583, 16, 22 });
	jump.PushBack({ 744, 583, 22, 21 });
	jump.PushBack({ 768, 583, 23, 23 });
	jump.PushBack({ 705, 583, 16, 19 });
	jump.loop = false;
	jump.speed = 0.1f;


	//walk left
	walk_l.PushBack({ 681, 558, 16, 23 });
	walk_l.PushBack({ 659, 558, 18, 21 });
	walk_l.PushBack({ 681, 556, 16, 23 });
	walk_l.PushBack({ 638, 556, 16, 22 });
	walk_l.loop = true;
	walk_l.speed = 0.2f;

	//jump left animation
	jump_l.PushBack({ 680, 583, 16, 19 });
	jump_l.PushBack({ 660, 583, 16, 22 });
	jump_l.PushBack({ 634, 583, 22, 21 });
	jump_l.PushBack({ 609, 583, 23, 23 });
	jump_l.PushBack({ 680, 583, 16, 19 });
	jump_l.loop = false;
	jump_l.speed = 0.1f;

	collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY, App->enemies);

	movement.loop = false;

	animation = &e1_forward;
	current_angle = angle;
	

	timer = SDL_GetTicks();

	if (sub_type == 2)
	{
		jumping = true;
	}
	else
	{
		movement.PushBack({ sinf((float)current_angle), cosf((float)current_angle) }, 100);
	}

	if (position.x < SCREEN_WIDTH / 2)
	{
		direction = 1;
		animation = &walk_l;
	}
	else
	{
		direction = -1;
		animation = &walk;
	}
}


EnemyLeft::~EnemyLeft()
{
}

void EnemyLeft::Move() {
	position = initial_position + movement.GetCurrentPosition();
	prev_position = position;
	iPoint player_pos = App->player->GetPosition();
	
		if (jumping == true)
		{

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
				movement.PushBack({ direction * 0.3f,0 }, 150);
				if (movement.Finished() == true)
				{
					jump_state = 2;
				}
			}
			else if (jump_state == 2)
			{
				if (direction == -1)
				{
					animation = &jump;
				}
				else if (direction == 1)
				{
					animation = &jump_l;
				}



				if (jump_state == 2)
				{
					movement.PushBack({ direction * 0.5f, jump_speed }, 200);
					jump_speed = jump_speed + 0.2f;
				}

				if (movement.Finished() == true)
				{
					jumping = false;
					current_angle = (rand() % 8) * 45;
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

		if ((movement.Finished() || collision == true) && dead == false && dying == false)
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
}

/*Animation* EnemyLeft::GetAnimationForDirection(int dir) {
	Animation* animation = nullptr;
	if (dir < 22 || dir > 338) 
	{
		shooting_position = { 3,14 };
		animation = &e1_forward;
	}
	
	else if (dir >= 22 && dir < 67)
	{
		shooting_position = { 0,6 };
		animation = &e1_up_left;
	}
	else if (dir >= 67 && dir < 112)
	{
		shooting_position = { 15,12 };
		animation = &e1_right;
	}
	else if (dir >= 112 && dir < 157)
	{
		shooting_position = { 9,15 };
		animation = &e1_down_left;
	}
	
	else if (dir >= 157 && dir < 202)
	{
		shooting_position = { 11,4 };
		animation = &e1_backward;
	}
		
	else if (dir >= 202 && dir < 247)
	{
		shooting_position = { 7,15 };
		animation = &e1_down_right;
	}
	
	else if (dir >= 247 && dir < 292)
	{
		shooting_position = { 2,12 };
		animation = &e1_left;
	}
	
	else if (dir >= 292 && dir < 338)
	{
		shooting_position = { 15,6 };
		animation = &e1_up_right;
	}
		
	return animation;
}*/

