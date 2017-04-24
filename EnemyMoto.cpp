#include "EnemyMoto.h"
#include "ModulePlayer.h"
#include "Application.h"


EnemyMoto::EnemyMoto(int x, int y) : Enemy(x, y)
{
	//riding

	riding.PushBack({1088, 43, 47, 22});
	riding.PushBack({ 1089, 75, 47, 21 });
	riding.speed = 0.5f;
	riding.loop = true;

	//throwing grenade
	throwing_grenade.PushBack({1087, 104, 46, 26});
	throwing_grenade.PushBack({ 1087, 135, 46, 25 });
	throwing_grenade.PushBack({ 1086, 169, 46, 26 });
	throwing_grenade.PushBack({ 1086, 200, 46, 26 });
	throwing_grenade.PushBack({ 1086, 232, 46, 26 });
	throwing_grenade.speed = 0.5f;
	throwing_grenade.loop = true;

	animation = &riding;
	

	movement.PushBack({ -0.1f, 0.0f }, 100, &riding);
	
	movement.loop = true;

}


EnemyMoto::~EnemyMoto()
{
}

void EnemyMoto::Move() {
	position = initial_position + movement.GetCurrentPosition();
	if (position.x <= SCREEN_WIDTH/2){

		if (App->player->GetPosition().y < position.y + 100 && movement.Finished())
		{

			movement.Clear();
			movement.Reset();

			movement.PushBack({ 0.0f, 0.0f }, 100, &throwing_grenade);
		}
		else if (movement.Finished())
		{
			movement.Clear();
			movement.Reset();

			movement.PushBack({ -0.1f, 0.0f }, 100, &riding);
		}
	}

}