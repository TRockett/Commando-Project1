#include "EnemyVehicles.h"
#include "ModulePlayer.h"
#include "Application.h"




EnemyVehicles::EnemyVehicles(int x, int y, int angle, int sub_type) : Enemy(x, y, angle, sub_type)
{
	//truck
	truck_riding.PushBack({129,68,255,250});

	//moto from right to left
	moto_rtol.PushBack({3, 212, 46, 22});

	//moto from left to right
	moto_rtol.PushBack({ 0, 175, 46, 22 });

	//vertical truck
	vertical_truck.PushBack({213, 51, 32, 46});
	vertical_truck.PushBack({ 213, 102, 32, 46 });
	vertical_truck.PushBack({ 213, 152, 32, 46 });

	vertical_truck.loop = true;
	vertical_truck.speed = 0.015f;

}


EnemyVehicles::~EnemyVehicles()
{
}

void EnemyVehicles::Move() {
	position = initial_position + movement.GetCurrentPosition(&animation);

	if (position.x <= SCREEN_WIDTH / 2) {
		iPoint player_pos = App->player->GetPosition();
		if (player_pos.y > position.y + 50)

		{
			movement.Clear();
			movement.Reset();
			animation = &moto_ltor;
			movement.PushBack({ -2.5f, 0.0f }, 10, &moto_ltor);
			movement.loop = true;
		}
	}
	else if (movement.Finished()) {
		movement.Reset();
	}

}