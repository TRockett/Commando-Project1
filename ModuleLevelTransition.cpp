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
	trans.speed = 0.15f;
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
	
	App->fade->FadeToBlack(this, App->level_4, 3.0f);


	return UPDATE_CONTINUE;
}

update_status ModuleLevelTransition::Update() {
	bool ret = false;

	string_2[actual] = string_1[actual];
	App->fonts->BlitText(15, 60, font_white, string_2);
	
	if (actual < strlen(string_1)) 
	{
		actual++;
	}
	App->render->Blit(background_graphics, 0, 0, nullptr, 0);

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