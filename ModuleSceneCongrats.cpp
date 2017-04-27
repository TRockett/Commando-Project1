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
#include "ModuleSceneGame.h"

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
	font_red = App->fonts->Load("Images/Fuentes_small_red.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	font_white = App->fonts->Load("Images/Fuentes_small_grey.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	App->scene_game->score_text;
	App->player->lives = 3;
	App->player->grenades = 6;
	App->scene_game->score = 0;
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
	sprintf_s(App->scene_game->score_text, 10, "%7d", App->scene_game->top_score);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleSceneCongrats::PostUpdate() {
	App->fonts->BlitText(60, (SCREEN_HEIGHT / 2 -30), font_red, "congratulations");
	App->fonts->BlitText(30, (SCREEN_HEIGHT / 2 ), font_red, "your best score");
	App->fonts->BlitText(130, (SCREEN_HEIGHT / 2  ), font_white, App->scene_game->score_text);
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