#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneGame.h"
#include "ModuleParticles.h"



ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x =150;
	position.y = 195;
	


	// idle forward position
	idle_forward.PushBack({ 0,0, 13, 23 });

	// idle backward position
	idle_backward.PushBack({ 28,24,13,22 });

	// idle right position
	idle_left.PushBack({ 160,0,19,22 });

	// idle left position
	idle_right.PushBack({ 42,0,19,22 });

	// walk forward animation (arcade sprite sheet)
	
	forward.PushBack({0, 0, 13, 23});
	forward.PushBack({14, 0, 13, 22});
	forward.PushBack({ 0, 0, 13, 23 });
	forward.PushBack({28, 0, 13, 22});
	forward.loop = true;
	forward.speed = 0.15f;

	//walk diagonal down-left

	down_left.PushBack({105,24,15,22});
	down_left.PushBack({120,24,15,22});
	down_left.PushBack({105,24,15,22 });
	down_left.PushBack({137,24,15,22});
	down_left.speed = 0.15f;

	//walk diagonal down-right

	down_right.PushBack({88,23,15,22});
	down_right.PushBack({56,23,15,22});
	down_right.PushBack({ 88,23,15,22 });
	down_right.PushBack({73,23,15,22});
	down_right.speed = 0.15f;

	//walk diagonal up-right

	up_right.PushBack({0,47,15,22});
	up_right.PushBack({38,47,18,21});
	up_right.PushBack({ 0,47,15,22 });
	up_right.PushBack({15,47,21,21});
	up_right.speed = 0.15f;

	//walk diagonal down-left

	up_left.PushBack({97,47,15,22});
	up_left.PushBack({56,47,18,21});
	up_left.PushBack({ 97,47,15,22 });
	up_left.PushBack({75,47,21,21});
	up_left.speed = 0.15f;

	//walk right animation

	
	right.PushBack({ 42,0,19,22 });
	right.PushBack({ 62,0,25,21 });
	right.PushBack({ 42,0,19,22 });
	right.PushBack({ 88,0,22,21 });
	right.loop = true;
	right.speed = 0.15f;
	

	//walk left annimation

	
	left.PushBack({ 160,0,19,22 });
	left.PushBack({ 134,0,25,21 });
	left.PushBack({ 160,0,19,22 });
	left.PushBack({ 111,0,19,22 });
	left.loop = true;
	left.speed = 0.15f;
	
	//walk backward animation

	backward.PushBack({ 28,24,13,22 });
	backward.PushBack({ 0,24,13,22 });
	backward.PushBack({ 28,24,13,22 });
	backward.PushBack({ 13,24,13,22 });
	backward.loop = true;
	backward.speed = 0.15f;
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	graphics = App->textures->Load("Images/sprites.png"); 
	current_animation= &idle_forward;
	return true;
}

bool ModulePlayer::CleanUp() {
	LOG("Unloading player");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	int speed = 1;
	direction.x = 0;
	direction.y = 0;

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		direction.x = 1;
		
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		direction.x = -1;
	}


	if(App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		direction.y = 1;
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;		
		direction.y = -1;
	}
	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->bullet,position.x, position.y, COLLIDER_PLAYER_SHOT);
	}

		if (direction.y == -1)
		{
			if (direction.x == -1)
			{
				if (current_animation != &down_left)
				{
					current_animation = &down_left;
					speed = 0.1f;

				}
			}
			else if (direction.x == 0)
			{
				if (current_animation != &backward)
				{
					current_animation = &backward;
				
				}
			}
			else if (direction.x == 1)
			{
				if (current_animation != &down_right)
				{
					current_animation = &down_right;
					speed = 0.1f;
				}
			}

		}
		else if (direction.y == 0)
		{
			
			if (direction.x == 1)
			{
				if (current_animation != &right)
				{
					current_animation = &right;

				}
			}
			else if (direction.x == -1)
			{
				if (current_animation != &left)
				{
					current_animation = &left;

				}
			}
		}
		else if (direction.y == 1)
		{
			if (direction.x == 0)
			{
				if (current_animation != &forward)
				{
					current_animation = &forward;
				}
			}
			else if (direction.x == 1)
			{
				if (current_animation != &up_right)
				{
					current_animation = &up_right;
					speed = 0.5f;
				}
			}
			else if (direction.x == -1)
			{
				if (current_animation != &up_left)
				{
					current_animation = &up_left;
					speed = 0.5f;
				}
			}
		}


	

	

	// Draw everything --------------------------------------
	//SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y , &(current_animation->GetCurrentFrame()));
	
	return UPDATE_CONTINUE;
}