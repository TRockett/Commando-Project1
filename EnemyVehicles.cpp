#include "EnemyVehicles.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleEnemies.h"



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
	vertical_truck.speed = 0.05f;
	vertical_truck.loop = true;


	//car with enemies left to right
	car_enemies_ltor.PushBack({1049, 345, 47, 25});

	//car with enemies right to left
	car_enemies_rtol.PushBack({ 1049, 371, 47, 25 });

	collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY_SHOT, nullptr);
	if (sub_type == 1)
	{

		direction = 1;
		animation = &moto_ltor;
		movement.PushBack({ 2.0f * direction, 0.0f }, 15, animation);
		movement.loop = true;
	}	
	else if (sub_type == 2)
	{
		direction = -1;
		animation = &moto_rtol;
		movement.PushBack({ 2.0f * direction, 0.0f }, 15, animation);
		movement.loop = true;
	}
	else if (sub_type == 3)
	{
		animation = &truck_riding;
		movement.PushBack({ -0.8f, 0.0f }, 40, animation);
		movement.PushBack({ 0.0f, 0.0f }, 40, animation);
		movement.loop = false;
	}
	else if (sub_type == 4)
	{
		direction = 1;
		animation = &car_enemies_ltor;
		movement.PushBack({ 1.2f * direction, 0.0f }, 15, animation);
		movement.loop = false;
		timer = SDL_GetTicks();
			
	}
	else if (sub_type == 5)
	{
		direction = -1;
		animation = &car_enemies_rtol;
		movement.PushBack({ 1.2f * direction, 0.0f }, 15, animation);
		movement.loop = true;
	}
	else if (sub_type == 6)
	{
		animation = &vertical_truck;
		animation->loop = false;
		movement.loop = false;
		shooting_position = { 11,39 };
		
	}
	
	move = false;
}


EnemyVehicles::~EnemyVehicles()
{
}

void EnemyVehicles::Move() 
{
	iPoint player_pos = App->player->GetPosition();

	if (sub_type == 1)
	{
		
		if (player_pos.y <= position.y + 10) 
		{
			move = true;
	 	}
		if (move == true)
		{
			position = initial_position + movement.GetCurrentPosition(&animation);
		}

	}
	else if (sub_type == 2)
	{
		if (player_pos.y <= position.y + 10) 
		{
			move = true;
			
		}
		if (move == true)
		{
			position = initial_position + movement.GetCurrentPosition(&animation);
		}

	}
	else if (sub_type == 3)
	{
		if (player_pos.y >= 692)
		{
			move = true;
		}
		if (move == true)
		{
			position = initial_position + movement.GetCurrentPosition(&animation);
			if (movement.Finished() == true)
			{
				App->enemies->AddEnemy(ENEMY_TRUCK, position.x, position.y, 0, 1);
				movement.Reset();
			}
		}
		
		

		
	}	
	else if (sub_type == 4)
	{
		if (player_pos.y <= position.y + 15)
		{
			move = true;
			
		}
		if (move == true)
		{
			position = initial_position + movement.GetCurrentPosition(&animation);
		}

	}
	else if (sub_type == 5)
	{
		if (player_pos.y <= position.y + 15)
		{
			move = true;
			
		}
		if (move == true)
		{
			position = initial_position + movement.GetCurrentPosition(&animation);
		}

	}
	else if (sub_type == 6)
	{
		if (move == true)
		{		
			position = initial_position + movement.GetCurrentPosition(&animation);
			if (movement.Finished() == true)
			{
				move = false;
			}			
		}
		else if (position.y + 100 >= player_pos.y)
		{
			move = true; 
			movement.PushBack({ 0.0f, -1.2f }, 150, animation);
			if (position.y <= 400)
			{

				movement.PushBack({ 0.0f, -49.9f }, 150, animation);
			}
		}

		if (animation->Finished() == true)
		{
			Particle molo = App->particles->molotov;
			molo.speed = { 0, 1 };
			App->particles->AddParticle(molo, position.x + shooting_position.x, position.y + shooting_position.y, MOLOTOV, COLLIDER_NONE);
			animation->Reset();
		}
		
		
	}	
}


	
	
