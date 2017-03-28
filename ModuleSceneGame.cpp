#include "ModuleSceneGame.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
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
	std::string str = "Images/Mapa";
	str.append(std::to_string(level));
	str.append(".png");
	background_graphics = App->textures->Load(str.c_str(), &initial_camera_pos);

	if (background_graphics == nullptr)
		ret = false;


	return ret;
}

update_status ModuleSceneGame::PreUpdate() {
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		level++;
		if (level > MAX_LEVEL) {
			level = 1;
			///Congrats screen
			//App->fade->FadeToBlack(this, )
		}
		else App->fade->FadeToBlack(this, this, 2.0f);
	}
	return UPDATE_CONTINUE;
}

update_status ModuleSceneGame::Update() {
	bool ret = true;
	//SDL_Rect target = { 0,0,189,216 };
	ret = App->render->Blit(background_graphics, 0, -initial_camera_pos.y + 216, nullptr);

	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
}

update_status ModuleSceneGame::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleSceneGame::CleanUp() {
	bool ret = true;

	ret = App->textures->Unload(background_graphics);

	return ret;
}