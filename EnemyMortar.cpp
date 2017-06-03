#include "EnemyMortar.h"
#include "Application.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleSceneGame.h"
#include "SDL/include/SDL_timer.h"
#include "ModulePlayer.h"


EnemyMortar::EnemyMortar(int x, int y, int angle, int sub_type, int isglobal) : Enemy(x, y, angle, sub_type, isglobal)
{
	mortar.PushBack({ 0,354,15,20 });
	mortar.PushBack({ 17,354,15,20 });
	mortar.PushBack({ 34,355,15,19 });
	mortar.loop = false;
	mortar.speed = 0.04f;

	collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY, App->enemies);

	shooting_position.y = 8;

	if (sub_type == 1)
	{
		shooting_position.x = 10;
	}
	else
	{
		shooting_position.x = 0;
	}
	animation = &mortar;
	current_angle = angle;

}


EnemyMortar::~EnemyMortar()
{
}

void EnemyMortar::Move()
{

	iPoint player_pos = App->player->GetPosition();


	if(animation->Finished() == true && dying == false)
	{
		animation->Reset();
		float deltaX = -position.x + player_pos.x;
		float deltaY = -position.y + player_pos.y;
		float angle = atan2f(deltaY, deltaX);
		float vec_mod = sqrtf(pow(deltaX, 2) + pow(deltaY, 2));
		fPoint normalised_v = { deltaX / vec_mod, deltaY / vec_mod };

		App->particles->Mortar_bomb.speed = { (float)(normalised_v.x * 1.0f), (float)(normalised_v.y * 1.0f) };
		App->particles->AddParticle(App->particles->Mortar_bomb, position.x + shooting_position.x, position.y + shooting_position.y, MORTAR_BOMB, COLLIDER_NONE,nullptr,0,1);
		timer = SDL_GetTicks();
	}
	if (dying == true)
	{
		animation = &death;
		collider->active = false;

		if (animation->Finished() == true)
		{
			dead = true;
			App->interfac->score += 500;
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
