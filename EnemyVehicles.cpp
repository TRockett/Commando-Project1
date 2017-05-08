#include "EnemyVehicles.h"
#include "ModulePlayer.h"
#include "Application.h"




EnemyVehicles::EnemyVehicles(int x, int y, int angle, int sub_type) : Enemy(x, y, angle, sub_type)
{
	//truck
	truck_riding.PushBack({1045,295,64,31});

	//moto from right to left
	moto_rtol.PushBack({976, 394, 45, 22});

	//moto from left to right
	moto_ltor.PushBack({ 973, 356, 46, 22 });

	//vertical truck
	vertical_truck.PushBack({1129, 278, 32, 46});
	vertical_truck.PushBack({ 1129, 329, 32, 46 });
	vertical_truck.PushBack({ 1129, 379, 32, 46 });


	vertical_truck.loop = true;
	vertical_truck.speed = 0.015f;

	if (sub_type == 2)
	{
		riding = true;
	}

	if (position.x < SCREEN_WIDTH / 2)
	{
		direction = 1;
		animation = &moto_ltor;
	}
	else
	{
		direction = -1;
		animation = &moto_rtol;
	}

}


EnemyVehicles::~EnemyVehicles()
{
}

void EnemyVehicles::Move() {
	position = initial_position + movement.GetCurrentPosition(&animation);
	if (riding == true) {
		if (position.x <= SCREEN_WIDTH) {
			iPoint player_pos = App->player->GetPosition();
			if (player_pos.y > position.y + 25)

			{
				movement.Clear();
				movement.Reset();
				animation = &moto_ltor;
				movement.PushBack({ 1.5f, 0.0f }, 15, &moto_ltor);
				movement.loop = true;
			}
		}
		else if (movement.Finished()) {
			movement.Reset();
		}
	}
}