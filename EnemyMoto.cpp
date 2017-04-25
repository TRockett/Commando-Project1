#include "EnemyMoto.h"
#include "ModulePlayer.h"
#include "Application.h"


EnemyMoto::EnemyMoto(int x, int y) : Enemy(x, y)
{
	//riding

	riding.PushBack({1088, 43, 47, 22});
	riding.PushBack({ 1089, 75, 47, 21 });
	riding.speed = 0.05f;
	riding.loop = true;

	//throwing grenade
	throwing_grenade.PushBack({1087, 104, 46, 26});
	throwing_grenade.PushBack({ 1087, 135, 46, 25 });
	throwing_grenade.PushBack({ 1086, 169, 46, 26 });
	throwing_grenade.PushBack({ 1086, 200, 46, 26 });
	throwing_grenade.PushBack({ 1086, 232, 46, 26 });
	throwing_grenade.speed = 0.1f;
	throwing_grenade.loop = false;	

	movement.PushBack({ -2.5f, 0.0f }, 10, &riding);
	
	movement.loop = false;

}


EnemyMoto::~EnemyMoto()
{
}

void EnemyMoto::Move() {
	position = initial_position + movement.GetCurrentPosition(&animation);
	if (position.x <= SCREEN_WIDTH/2){
		iPoint player_pos = App->player->GetPosition();
		if (player_pos.y > position.y + 50)
		{
			if (animation != &throwing_grenade) {
				movement.Clear();
				movement.Reset();
				movement.PushBack({ 0.0f, 0.0f }, 10, &throwing_grenade);
			}
			else if (animation->Finished()) {
				float deltaX = - position.x + player_pos.x;
				float deltaY = - position.y + player_pos.y;
				float angle = atan2f(deltaY, deltaX);
				
				App->particles->grenade.speed = { (float)(deltaX * 0.015f /** cosf(angle)*/), (float)(deltaY * 0.015f /** sinf(angle)*/) };
				App->particles->AddParticle(App->particles->grenade, position.x, position.y, GRENADE_ENEMY, COLLIDER_NONE);
				animation->Reset();
			}
		}
		else if (animation->Finished())
		{
			movement.Clear();
			movement.Reset();

			movement.PushBack({ -2.5f, 0.0f }, 10, &riding);
			movement.loop = true;
		}
	}
	else if (movement.Finished()) {
		movement.Reset();
	}

}