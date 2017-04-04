#include "ModuleSceneCongrats.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneWelcome.h"
#include "ModuleSound.h"


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

	background_graphics = App->textures->Load("Images/Mapa1.png");

	if (background_graphics == nullptr)
		ret = false;

	if (App->sound->LoadMusic("Soundtrack/13. Namen eingeben.wav") == nullptr)
		ret = false;

	return ret;
}

update_status ModuleSceneCongrats::PreUpdate() {
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(this, App->scene_welcome, 1.0f);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleSceneCongrats::Update() {
	SDL_Rect target = { 20, 465, 216, 256 };
	App->render->Blit(background_graphics, 0, 0, &target, 0.0f);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleSceneCongrats::PostUpdate() {
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