#include "ModuleSceneCongrats.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneWelcome.h"
#include "ModuleSound.h"
#include "ModuleFonts.h"

ModuleSceneCongrats::ModuleSceneCongrats()
{
}


ModuleSceneCongrats::~ModuleSceneCongrats()
{
}

bool ModuleSceneCongrats::Init() {
	return true;
}

bool ModuleSceneCongrats::Start() {
	bool ret = true;
	font = App->fonts->Load("Images/Fuentes_small_red.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 2);

	App->player->lives = 3;
	background_graphics = App->textures->Load("Images/Mapa1.png");

	if (background_graphics == nullptr)
		ret = false;

	if (App->sound->LoadMusic("Soundtrack/13. Namen eingeben.wav") == nullptr)
		ret = false;

	return ret;
}

update_status ModuleSceneCongrats::PreUpdate() {
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
		App->fade->FadeToBlack(this, App->scene_welcome, 1.0f);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleSceneCongrats::Update() {
	SDL_Rect target = { 20, 465, 216, 256 };
	App->render->Blit(background_graphics, 0, 0, &target, 0.0f);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleSceneCongrats::PostUpdate() {
	App->fonts->BlitText(30, (SCREEN_HEIGHT / 2), font, "CONGRATULATIONS");
	return update_status::UPDATE_CONTINUE;
}

bool ModuleSceneCongrats::CleanUp() {
	bool ret = true;
	App->sound->StopAll();
	return ret;
}

void ModuleSceneCongrats::onFadeInEnd() {
	App->sound->PlayMusic();
}