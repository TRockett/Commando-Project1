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


	new_str = (char*)calloc(strlen(string_1) + 1, sizeof(char));
	timer = SDL_GetTicks();
	return true;
}

bool ModuleLevelTransition::Start() {



	bool ret = true;
	App->fonts->Enable();
	App->interfac->Enable();
	background_graphics = App->textures->Load("Images/trans2.png");
	font_red = App->fonts->Load("Images/Fuentes_small_red.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	font_white = App->fonts->Load("Images/Fuentes_small_grey.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);

	App->interfac->AddLabel(font_red, "1UP", 15, 0);
	App->interfac->AddLabel(font_red, "TOP SCORE", SCREEN_WIDTH / 2 - 30, 0);
	App->interfac->AddLabel(font_white, App->interfac->score_texts[0], SCREEN_WIDTH / 2 - 15, 8);

	label = App->interfac->getLabel(App->interfac->AddLabel(font_white, "", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50));
	sprite_graphics = App->textures->Load("Images/sprites.png");

	trans.PushBack({ 0, 737, 32, 52 });
	trans.PushBack({ 42, 737, 32, 52 });
	trans.PushBack({ 82, 737, 32, 53 });
	trans.loop = true;
	trans.speed = 0.15f;

	if (background_graphics == nullptr)
		ret = false;
	
	return ret;
}

update_status ModuleLevelTransition::PreUpdate() {
	return UPDATE_CONTINUE;
}

update_status ModuleLevelTransition::Update() {
	bool ret = false;

	ret = App->render->Blit(background_graphics, 0, 0, nullptr, 0.2f);
	App->render->Blit(sprite_graphics, SCREEN_HEIGHT, SCREEN_WIDTH, &trans.GetCurrentFrame().rect);
	
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
		else App->fade->FadeToBlack(this, App->level_4, 5);
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