#include "Application.h"
#include "EnemyTower.h"
#include"ModulePlayer.h"
#include"ModuleLevel4.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleEnemies.h"


EnemyTower::EnemyTower(int x, int y, int angle, int sub_type, int isglobal) : Enemy(x, y, angle, sub_type, isglobal)
{
	anim1.PushBack({ 134,143 ,16,13 });
	anim2.PushBack({ 152,143,14,14 });
	anim3.PushBack({ 168,143,16,15 });
	anim4.PushBack({ 185,143,16,15 });

	anim_right.PushBack({ 151,128,15,16 });
	anim_right2.PushBack({ 168,128,14,14 });
	anim_right3.PushBack({ 185,128,16,13 });
	
	if (sub_type == 1)
	{
		collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_NONE, App->enemies);
	}
	else
	{
		collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY, App->enemies);
	}
}

void EnemyTower::Move()
{
	iPoint player_pos = App->player->GetPosition();
	if (sub_type == 1)
	{
		if (player_pos.x < SCREEN_WIDTH / 4 )
		{
			animation = &anim1;
			shooting_position.x = 0;
			shooting_position.y = 13;
		}
		else if (player_pos.x >= SCREEN_WIDTH / 4 && player_pos.x < ((SCREEN_WIDTH / 4) * 2))
		{
			animation = &anim2;
			shooting_position.x = 0;
			shooting_position.y = 14;
		}
		else if (player_pos.x >= ((SCREEN_WIDTH / 4) * 2) / 4 && player_pos.x < ((SCREEN_WIDTH / 4) * 3))
		{
			animation = &anim3;
			shooting_position.x = 5;
			shooting_position.y = 15;
		}
		else if (player_pos.x >= ((SCREEN_WIDTH / 4) * 3) / 4 && player_pos.x < SCREEN_WIDTH || player_pos.y >= position.y)
		{
			animation = &anim4;
			shooting_position.x = 7;
			shooting_position.y = 15;
		}
	}
	else
	{
		if (player_pos.x < position.x - 50)
		{
			animation = &anim1;
			shooting_position.x = 0;
			shooting_position.y = 13;
		}
		else if (player_pos.x < position.x - 50 && player_pos.x >= position.x - 30)
		{	
			animation = &anim2;
			shooting_position.x = 0;
			shooting_position.y = 14;
		}
		else if (player_pos.x >= position.x - 30 && player_pos.x < position.x - 10)
		{
			animation = &anim3;
			shooting_position.x = 5;
			shooting_position.y = 15;
		}
		else if (player_pos.x >= position.x - 10 && player_pos.x < position.x + 10)
		{
			animation = &anim4;
			shooting_position.x = 7;
			shooting_position.y = 15;
		}
		else if (player_pos.x >= position.x + 10 && player_pos.x < position.x + 30)
		{
			animation = &anim_right;
			shooting_position.x = 11;
			shooting_position.y = 15;
		}
		else if (player_pos.x >= position.x + 30 && player_pos.x < position.x + 50)
		{
			animation = &anim_right2;
			shooting_position.x = 12;
			shooting_position.y = 14;
		}
		else if (player_pos.x >= position.x + 50)
		{
			animation = &anim_right3;
			shooting_position.x = 14;
			shooting_position.y = 15;
		}
	}
	if (SDL_GetTicks() >= timer + 1500)
	{
		float deltaX = -position.x + player_pos.x;
		float deltaY = -position.y + player_pos.y;
		float angle = atan2f(deltaY, deltaX);
		float vec_mod = sqrtf(pow(deltaX, 2) + pow(deltaY, 2));
		fPoint normalised_v = { deltaX / vec_mod, deltaY / vec_mod };

		App->particles->bullet.speed = { (float)(normalised_v.x * 1.2f), (float)(normalised_v.y * 1.2f) };
		App->particles->bullet.life = 2000;
		App->particles->AddParticle(App->particles->bullet, position.x + shooting_position.x, position.y + shooting_position.y, BULLET_ENEMY, COLLIDER_ENEMY_SHOT2);
		timer = SDL_GetTicks();
	}
	if (dying == true)
	{
		animation = &death;
		collider->active = false;


		if (animation->Finished() == true)
		{
			dead = true;
			App->interfac->score += 200;
			//App->scene_game->screen_enemies--;
			App->enemies->EraseEnemy(this);
		}
	}

	else if (disappear == true)
	{
		animation = &death;
		collider->active = false;


		if (animation->Finished() == true)
		{
			dead = true;
			//App->scene_game->screen_enemies--;
			App->enemies->EraseEnemy(this);
		}
	}
}
EnemyTower::~EnemyTower()
{
}
