#include "Application.h"
#include "EnemyTower.h"
#include"ModulePlayer.h"
#include"ModuleLevel4.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleEnemies.h"


EnemyTower::EnemyTower(int x, int y, int angle, int sub_type) : Enemy(x, y, angle, sub_type)
{
	anim1.PushBack({ 134,144 ,16,13 });
	anim2.PushBack({ 152,144,14,14 });
	anim3.PushBack({ 168,144,16,15 });
	anim4.PushBack({ 185,144,16,15 });
	
	collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_NONE, App->enemies);
}

void EnemyTower::Move()
{
	iPoint player_pos = App->player->GetPosition();

	if (player_pos.x < SCREEN_WIDTH / 4)
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
	else if (player_pos.x >= ((SCREEN_WIDTH / 4) * 3) / 4 && player_pos.x <SCREEN_WIDTH)
	{
		animation = &anim4;
		shooting_position.x = 7;
		shooting_position.y = 15;
	}

	if (SDL_GetTicks() >= timer + 800)
	{
		float deltaX = -position.x + player_pos.x;
		float deltaY = -position.y + player_pos.y;
		float angle = atan2f(deltaY, deltaX);
		float vec_mod = sqrtf(pow(deltaX, 2) + pow(deltaY, 2));
		fPoint normalised_v = { deltaX / vec_mod, deltaY / vec_mod };

		App->particles->bullet.speed = { (float)(normalised_v.x * 1.2f), (float)(normalised_v.y * 1.2f) };
		App->particles->bullet.life = 2000;
		App->particles->AddParticle(App->particles->bullet, position.x + shooting_position.x, position.y + shooting_position.y, BULLET_ENEMY, COLLIDER_ENEMY_SHOT);
		timer = SDL_GetTicks();
	}
}
EnemyTower::~EnemyTower()
{
}
