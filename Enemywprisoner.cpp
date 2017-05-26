#include "Enemywprisoner.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleSceneGame.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

Enemywprisoner::Enemywprisoner(int x, int y, int angle, int sub_type, int isglobal) : Enemy (x, y, angle, sub_type, isglobal)
{
	//soldier left

		//walk soldier left
	walk.PushBack({928, 243, 16, 22});
	walk.PushBack({ 963, 243, 16, 22 });
	walk.PushBack({ 998, 243, 16, 22 });

		//death solider left
	death.PushBack({934, 277, 24, 11});


	//soldier right

		//walk soldier right
	walk_2.PushBack({ 928, 243, 16, 22 });
	walk_2.PushBack({ 963, 243, 16, 22 });
	walk_2.PushBack({ 998, 243, 16, 22 });

		//death solider left
	death_2.PushBack({ 934, 277, 24, 11 });


	//prisoner

		//walk 
	walk_3.PushBack({944,243,16,22});
	walk_3.PushBack({ 979,243,16,22 });
	walk_3.PushBack({ 1014,243,16,22 });

		//free

	free.PushBack({969, 272, 15, 22});
	free.PushBack({ 986, 272, 14, 22 });

		//free dancing
	free_d.PushBack({ 1002, 269, 16, 25 });
	free_d.PushBack({ 1020, 271, 24, 23 });
	



	movement.PushBack({ 3.0f, 3.0f }, 100, animation);

	animation = &walking;

	movement.loop = false;
};


Enemywprisoner::~Enemywprisoner()
{
};

void Enemywprisoner::Move() {
	if (App->player->position.y >= 1212)
	{
		this->position.x++;
		this->position.y++;

		position = initial_position + movement.GetCurrentPosition();
		prev_position = position;
		iPoint player_pos = App->player->GetPosition();

		if ((movement.Finished()) && dead == false && dying == false)
		{
			movement.Clear();
			movement.Reset();

		}
		else if (dying == true)
		{
			animation = &death;
			App->collision->EraseCollider(this->collider);
			movement.Clear();
			movement.Reset();

			if (animation->Finished() == true)
			{
				dead = true;
				App->scene_game->score = App->scene_game->score + 200;
				App->scene_game->screen_enemies--;
				App->enemies->EraseEnemy(this);
			}
		}
	}
}