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

	//car with enemies left to right
	car_enemies_ltor.PushBack({1049, 345, 47, 25});

	//car with enemies right to left
	car_enemies_rtol.PushBack({ 1049, 371, 47, 25 });
	
	if (sub_type == 1)
	{

		direction = 1;
		animation = &moto_ltor;


	}
	else
	{
		if (sub_type == 3)
		{
			direction = -1;
			animation = &truck_riding;
		}
		else if (sub_type == 2)
		{
			direction = -1;
			animation = &moto_rtol;
		}

		else if (sub_type == 4)
		{
			direction = 1;
			animation = &car_enemies_ltor;
		}
		else if (sub_type == 5)
		{
			direction = -1;
			animation = &car_enemies_rtol;
		}
		
	}

}


EnemyVehicles::~EnemyVehicles()
{
}

void EnemyVehicles::Move() {
	position = initial_position + movement.GetCurrentPosition(&animation);

	if ((position.x <= SCREEN_WIDTH && animation == &moto_ltor) || (position.x >= 0 && animation == &moto_rtol || (position.x >= 0 && animation == &truck_riding)|| position.x <= SCREEN_WIDTH && animation == &car_enemies_ltor)|| (position.x >= 0 && animation == &car_enemies_rtol))
	{
		iPoint player_pos = App->player->GetPosition();
		if (player_pos.y > position.y + 25)
		{
			movement.Clear();
			movement.Reset();
			movement.PushBack({ 1.0f * direction, 0.0f }, 15, animation);
			movement.loop = true;
		}
	}
	else if (movement.Finished()) {
		movement.Reset();
	}
}