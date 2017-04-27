#include "EnemyGrenade.h"
#include "ModulePlayer.h"
#include "Application.h"

EnemyGrenade::EnemyGrenade(int x, int y) : Enemy (x,y) 
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
};


EnemyGrenade::~EnemyGrenade()
{
}

//void EnemyGrenade::Move()
//{
//	iPoint player_pos = App->player->GetPosition();
//	if (player_pos.y > position.y + 50)
//	{
//		if (animation != &throwing_grenade) {
//			movement.Clear();
//			movement.Reset();
//			movement.PushBack({ 0.0f, 0.0f }, 10, &throwing_grenade);
//		}
//		else if (animation->Finished()) {
//			float deltaX = -position.x + player_pos.x;
//			float deltaY = -position.y + player_pos.y;
//			float angle = atan2f(deltaY, deltaX);
//
//			App->particles->grenade.speed = { (float)(deltaX * 0.015f /** cosf(angle)*/), (float)(deltaY * 0.015f /** sinf(angle)*/) };
//			App->particles->AddParticle(App->particles->grenade, position.x, position.y, GRENADE_ENEMY, COLLIDER_NONE);
//			animation->Reset();
//		}
//}

