#include "EnemyVehicles.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "SDL/include/SDL_timer.h"



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

	collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY_SHOT, nullptr);
	if (sub_type == 1)
	{

		direction = 1;
		animation = &moto_ltor;
		movement.PushBack({ 2.0f * direction, 0.0f }, 15, animation);
		movement.loop = true;
	}
	else
	{
		if (sub_type == 3)
		{
			direction = -1;
			animation = &truck_riding;
			movement.PushBack({ 0.8f * direction, 0.0f }, 40, animation);
			movement.PushBack({ 0.0f, 0.0f }, 40, animation);
			movement.loop = true;
		}
		else if (sub_type == 2)
		{
			direction = -1;
			animation = &moto_rtol;
			movement.PushBack({ 2.0f * direction, 0.0f }, 15, animation);
			movement.loop = true;
		}

		else if (sub_type == 4)
		{
			direction = 1;
			animation = &car_enemies_ltor;
			movement.PushBack({ 1.2f * direction, 0.0f }, 15, animation);
			movement.loop = true;
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
			movement.PushBack({ 0.0f, -1.0f }, 300, animation);
			movement.PushBack({ 0.0f, 0.0f }, 50, animation);
			
			movement.loop = true;

			if (App->player->position.y == 400) 
			{
				movement.PushBack({ 0.0f, -50.0f }, 500, animation);
			}
		}
	}

}


EnemyVehicles::~EnemyVehicles()
{
}

void EnemyVehicles::Move() {
	iPoint player_pos = App->player->GetPosition();

	
	if (sub_type == 3)
	{
		if (player_pos.y >= 692)
		{
			position = initial_position + movement.GetCurrentPosition(&animation);
		}
	}

	if (sub_type == 1)
	{
		if (player_pos.y <= position.y +10) {
			position = initial_position + movement.GetCurrentPosition(&animation);
		}

	}
	if (sub_type == 2)
	{
		if (player_pos.y <= position.y + 10) {
			position = initial_position + movement.GetCurrentPosition(&animation);
		}

	}
	if (sub_type == 4)
	{
		if (player_pos.y <= position.y + 15)
		{
			position = initial_position + movement.GetCurrentPosition(&animation);
		}
		//if (player_pos.y > position.y)
		//{
		//	if (SDL_GetTicks() >= timer + 200)
		//	{

		//		float deltaX = -position.x + player_pos.x;
		//		float deltaY = -position.y + player_pos.y;
		//		float angle = atan2f(deltaY, deltaX);
		//		float vec_mod = sqrtf(pow(deltaX, 2) + pow(deltaY, 2));
		//		fPoint normalised_v = { deltaX / vec_mod, deltaY / vec_mod };

		//		App->particles->bullet.speed = { (float)(normalised_v.x * 1.0f), (float)(normalised_v.y * 1.0f) };
		//		App->particles->bullet.life = 1800;
		//		App->particles->AddParticle(App->particles->bullet, position.x + shooting_position.x, position.y + shooting_position.y, BULLET_ENEMY, COLLIDER_ENEMY_SHOT);
		//		timer = SDL_GetTicks();
		//	}
		//}
	}

	else if (sub_type == 5)
	{
		if (player_pos.y <= position.y + 15)
		{
			position = initial_position + movement.GetCurrentPosition(&animation);
		}

		/*if (player_pos.y > position.y)
		{
			if (SDL_GetTicks() >= timer + 200)
			{
				float deltaX = -position.x + player_pos.x;
				float deltaY = -position.y + player_pos.y;
				float angle = atan2f(deltaY, deltaX);
				float vec_mod = sqrtf(pow(deltaX, 2) + pow(deltaY, 2));
				fPoint normalised_v = { deltaX / vec_mod, deltaY / vec_mod };

				App->particles->bullet.speed = { (float)(normalised_v.x * 1.0f), (float)(normalised_v.y * 1.0f) };
				App->particles->bullet.life = 1800;
				App->particles->AddParticle(App->particles->bullet, position.x + shooting_position.x, position.y + shooting_position.y, BULLET_ENEMY, COLLIDER_ENEMY_SHOT);
				timer = SDL_GetTicks();
			}
		}*/
	}
	if (sub_type == 6)
	{
		/*if (position.y > 350) {*/
			if (position.y + 150 <= position.y >= position.y)
			{
				if (SDL_GetTicks() >= timer + 10)
				{
					position = initial_position + movement.GetCurrentPosition(&animation);

				}


		/*	}*/



			else if (player_pos.y <= position.y + 8)
			{
				position = initial_position + movement.GetCurrentPosition(&animation);
			}
		}
		
		//else 
		//{
		//	//increase speed until the end of the map

		//}
	
	}


	
	
}