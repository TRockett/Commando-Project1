#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneGame.h"



ModulePlayer::ModulePlayer()
{


	// walk forward animation (arcade sprite sheet)
	
	forward.PushBack({0, 0, 13, 23});
	forward.PushBack({0, 14, 13, 22});
	forward.PushBack({0, 28, 13, 22});
	forward.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	player_rect.y = 200;
	player_rect.x = 200;
	player_rect.h = 23;
	player_rect.w = 13;

	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Images/sprites.png"); 
	return ret;
}

bool ModulePlayer::CleanUp() {
	bool ret = true;
	ret = App->textures->Unload(graphics);
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &forward;

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &forward;
	
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, player_rect.x, player_rect.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}