#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneGame.h"



ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x =150;
	position.y = 195;
	


	// idle position
	idle.PushBack({ 0,0, 13, 23 });

	// walk forward animation (arcade sprite sheet)
	
	forward.PushBack({0, 0, 13, 23});
	forward.PushBack({14, 0, 13, 22});
	forward.PushBack({ 0, 0, 13, 23 });
	forward.PushBack({28, 0, 13, 22});
	
	forward.speed = 0.15f;

	//walk diagonal down-left

	down_left.PushBack({115,23,15,22});
	down_left.PushBack({121,23,15,22});
	down_left.PushBack({ 115,23,15,22 });
	down_left.PushBack({137,23,15,22});

	//walk diagonal down-right

	down_right.PushBack({88,23,15,22});
	down_right.PushBack({56,23,15,22});
	down_right.PushBack({ 88,23,15,22 });
	down_right.PushBack({73,23,15,22});

	//walk diagonal up-right

	up_right.PushBack({});
	up_right.PushBack({});
	up_right.PushBack({});

	//walk diagonal down-left

	up_left.PushBack({});
	up_left.PushBack({});
	up_left.PushBack({});


	//walk right animation

	
	right.PushBack({ 42,0,19,22 });
	right.PushBack({ 62,0,25,21 });
	right.PushBack({ 42,0,19,22 });
	right.PushBack({ 88,0,22,21 });
	right.speed = 0.15f;
	

	//walk left annimation

	
	left.PushBack({ 160,0,19,22 });
	left.PushBack({ 134,0,25,21 });
	left.PushBack({ 160,0,19,22 });
	left.PushBack({ 111,0,19,22 });
	left.speed = 0.15f;
	
	//walk backward animation

	backward.PushBack({ 28,24,13,22 });
	backward.PushBack({ 0,24,13,22 });
	backward.PushBack({ 28,24,13,22 });
	backward.PushBack({ 13,24,13,22 });
	
	backward.speed = 0.15f;
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	graphics = App->textures->Load("Images/sprites.png"); 
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
	Animation* current_animation = &idle;

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		position.x += speed;
		if (current_animation != &right)
		{
			current_animation = &right;

		}
	}
	if (App->input->keyboard[SDL_SCANCODE_A] ==1)
	{
		position.x -= speed;
		if (current_animation != &left)
		{
			current_animation = &left;
		}
	}


	if(App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		position.y -= speed;
		if (current_animation != &forward)
		{
			current_animation = &forward;
			
		}
	
	}

	if (App->input->keyboard[SDL_SCANCODE_S] ==1)
	{
		position.y += speed;
		if (current_animation != &backward)
		{
			current_animation = &backward;
			
		}
	}

	// Draw everything --------------------------------------
	//SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y , &(current_animation->GetCurrentFrame()));
	
	return UPDATE_CONTINUE;
}