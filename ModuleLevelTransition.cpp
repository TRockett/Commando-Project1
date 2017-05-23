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
#include "ModuleInterface.h"
#include "SDL/include/SDL_timer.h"

ModuleLevelTransition::ModuleLevelTransition()
{
}


ModuleLevelTransition::~ModuleLevelTransition()
{
}






bool ModuleLevelTransition::Init() {
	trans.PushBack({ 678, 380, 32, 52 });
	trans.PushBack({ 678, 328, 32, 52 });
	trans.PushBack({ 500, 0, 224, 256 });
	trans.loop = true;
	trans.speed = 0.015f;

	new_str = (char*)calloc(strlen(string_1), sizeof(char));
	timer = SDL_GetTicks();
	return true;
}

bool ModuleLevelTransition::Start() {
	bool ret = true;
	App->fonts->Enable();
	App->interfac->Enable();
	background_graphics = App->textures->Load("Images/sprites.png");
	font_red = App->fonts->Load("Images/Fuentes_small_red.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	font_white = App->fonts->Load("Images/Fuentes_small_grey.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	
	App->interfac->AddLabel(font_red, "1up", 15, 0);
	App->interfac->AddLabel(font_red, "top score", SCREEN_WIDTH / 2 - 30, 0);
	App->interfac->AddLabel(font_white, "50000", SCREEN_WIDTH / 2 - 15, 8);
	label = App->interfac->getLabel(App->interfac->AddLabel(font_white, "", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50));

	if (background_graphics == nullptr)
		ret = false;
	
	return ret;
}

update_status ModuleLevelTransition::PreUpdate() {
	return UPDATE_CONTINUE;
}

update_status ModuleLevelTransition::Update() {
	bool ret = false;

	ret = App->render->Blit(background_graphics, 0, 0, nullptr, 0);
	if (label != nullptr) {
		//for (uint i = 0; i <= actual; i++)
		new_str[actual] = string_1[actual];
		label->setString(new_str);
	}

	if (SDL_GetTicks() >= timer + 100)
	{
		if (actual < strlen(string_1)) {
			actual++;
		}
		else App->fade->FadeToBlack(this, App->level_4, 8);
		timer = SDL_GetTicks();
	}
	
	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;

}

update_status ModuleLevelTransition::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleLevelTransition::CleanUp() {
	bool ret = true;
	App->fonts->Disable();
	App->interfac->Disable();
	ret = App->textures->Unload(background_graphics);




	return ret;
}