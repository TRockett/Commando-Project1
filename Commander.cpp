#include "Commander.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "SDL/include/SDL_timer.h"
#include <math.h>
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleSceneGame.h"


Commander::Commander(int x, int y, int angle, int sub_type) : Enemy(x, y, angle, sub_type)
{
	current_angle = angle;

	collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY, App->enemies);

	movement.loop = false;
	movement.PushBack({ sinf((float)current_angle*(M_PI / 180.0f)), cosf((float)current_angle*(M_PI / 180.0f)) }, 0);

	e1_left.PushBack({ 219,357,15,23 });
	e1_left.PushBack({ 202,357,16,21 });
	e1_left.PushBack({ 219,357,15,23 });
	e1_left.PushBack({ 235,357,20,22 });
	e1_left.loop = true;
	e1_left.speed = 0.15f;

	e1_right.PushBack({ 169,357,15,23 });
	e1_right.PushBack({ 148,357,20,22 });
	e1_right.PushBack({ 169,357,15,23 });
	e1_right.PushBack({ 185,357,16,21 });
	e1_right.loop = true;
	e1_right.speed = 0.15f;
	e1_down_left = e1_left;
	e1_down_right = e1_right;
	e1_up_right = e1_right;
	e1_up_left = e1_left;

	death.PushBack({ 68 ,489, 25 ,11 });
	death.speed = 0.02f;

	animation = &e1_left;
}


Commander::~Commander()
{
}

void Commander::Move() {
	position = initial_position + movement.GetCurrentPosition();
	prev_position = position;
	iPoint player_pos = App->player->GetPosition();


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
				current_angle = ((rand() % 4) * 45) - 90;
				if (current_angle < 0)
				{
					current_angle += 450;
				}
			}
			else
			{
				position = prev_position;
				current_angle = Collisionangle(current_angle);
			}

			animation = GetAnimationForDirection(current_angle);
			movement.PushBack({ sinf((float)current_angle *(M_PI / 180.0f)), cosf((float)current_angle *(M_PI / 180.0f)) }, 200);
			collision = false;
		}
		else if (dying == true)
		{
			animation = &death;
			collider->to_delete = true;
			movement.Clear();
			movement.Reset();

			if (animation->Finished() == true)
			{
				dead = true;
				App->scene_game->score = App->scene_game->score + 2000;
				App->scene_game->screen_enemies--;
				App->enemies->EraseEnemy(this);
			}
		}

		else if (disappear == true)
		{
			animation = &death;
			collider->to_delete = true;
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
