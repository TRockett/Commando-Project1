#include "ModuleSceneGame.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneCongrats.h"
#include "ModuleSound.h"
#include <string>


ModuleSceneGame::ModuleSceneGame()
{
}


ModuleSceneGame::~ModuleSceneGame()
{
}

bool ModuleSceneGame::Init() {
	level = 1;
	return true;
}

bool ModuleSceneGame::Start() {
	bool ret = true;

	App->player->Enable();
	std::string str = "Images/Mapa";
	str.append(std::to_string(level));
	str.append(".png");
	background_graphics = App->textures->Load(str.c_str(), &initial_camera_pos);

	if (background_graphics == nullptr)
		ret = false;

	if (App->sound->LoadMusic("Soundtrack/3.Hintergrundmusik 1.wav") == nullptr)
		ret = false;
	
	return ret;
}

update_status ModuleSceneGame::PreUpdate() {
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		if (level + 1 > MAX_LEVEL) {
			if (App->fade->FadeToBlack(this, App->scene_congrats, 2.0f)) {
				level = 1;
			}
		}
		else {
			if (App->fade->FadeToBlack(this, this, 1.0f)) {
				level++;
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleSceneGame::Update() {
	bool ret = true;
	if (-initial_camera_pos.y + SCREEN_HEIGHT + targetY < 0 && moving)
		targetY++;
	targetY = App->player->position.y-10;
	SDL_Rect target = { 10, App->player->position.y, 216, 256 };
	ret = App->render->Blit(background_graphics, 0, 0, &target);

	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
}

update_status ModuleSceneGame::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleSceneGame::CleanUp() {
	bool ret = true;
	targetY = 0;
	moving = false;
	App->sound->StopAll();
	if (!ret) {
		App->textures->Unload(background_graphics);
		return ret;
	}
	ret = App->textures->Unload(background_graphics);

	return ret;
}

void ModuleSceneGame::onFadeInEnd() {
	moving = true;
	App->sound->PlayMusic();
}