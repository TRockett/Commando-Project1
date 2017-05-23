#include "ModuleLevelTransition.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneGame.h"
#include "ModuleSound.h"
#include "ModuleFonts.h"
#include"ModuleLevel3.h"
#include "ModuleLevel4.h"
#include "SDL/include/SDL_timer.h"



ModuleLevelTransition::ModuleLevelTransition()
{
}


ModuleLevelTransition::~ModuleLevelTransition()
{
}






bool ModuleLevelTransition::Init() {
	trans.PushBack({224,0, 224, 256});
	trans.PushBack({ 250,0, 224, 256 });
	trans.PushBack({ 500,0, 224, 256 });
	trans.loop = true;
	trans.speed = 0.01f;

	string_2 = (char*)calloc(strlen(string_1), sizeof(char));
	string_4 = (char*)calloc(strlen(string_3), sizeof(char));

	timer = SDL_GetTicks();
	return true;
}

bool ModuleLevelTransition::Start() {
	bool ret = true;
	App->fonts->Enable();
	background_graphics = App->textures->Load("Images/trans.png");
	font_red = App->fonts->Load("Images/Fuentes_small_red.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	font_white = App->fonts->Load("Images/Fuentes_small_grey.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	
	if (background_graphics == nullptr)
		ret = false;
	
	return ret;
}

update_status ModuleLevelTransition::PreUpdate() {
	
	App->fade->FadeToBlack(this, App->level_4, 40);


	return UPDATE_CONTINUE;
}

update_status ModuleLevelTransition::Update() {
	bool ret = false;

	ret = App->render->Blit(background_graphics, 0, 0, nullptr, 0);


	string_2[actual] = string_1[actual];
	App->fonts->BlitText(5, 60, font_white, string_2);
	
	if (SDL_GetTicks() >= timer + 100)
	{
		if (actual < strlen(string_1))
		{
			actual++;
		}
		else if (actual_2 < strlen(string_3))
		{
			actual_2++;
		}
		timer = SDL_GetTicks();
	}
	string_4[actual_2] = string_3[actual_2];
	if (actual >= strlen(string_1))
	{
		App->fonts->BlitText(5, 80, font_white, string_4);
	}
	
	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;

}

update_status ModuleLevelTransition::PostUpdate() {
	App->fonts->BlitText(15, 0, font_red, "1up");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 30, 0, font_red, "top score");
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 15, 8, font_white, "50000");
	return UPDATE_CONTINUE;
}

bool ModuleLevelTransition::CleanUp() {
	bool ret = true;
	App->fonts->Disable();
	ret = App->textures->Unload(background_graphics);




	return ret;
}