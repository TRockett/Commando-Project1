#include "ModuleSceneWelcome.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneKen.h"


ModuleSceneWelcome::ModuleSceneWelcome()
{
}


ModuleSceneWelcome::~ModuleSceneWelcome()
{
}


bool ModuleSceneWelcome::Init() {
	for (int i = 0; i < BACKGROUND_NUMBER; i++) {
		background_graphics[i] = nullptr;
	}
	return true;
}

bool ModuleSceneWelcome::Start() {
	background_graphics[0] = App->textures->Load("../Images/0006.png");
	background_graphics[1] = App->textures->Load("../Images/0007.png");
	background_graphics[2] = App->textures->Load("../Images/0000.png");
	bool ret = true;
	for (int i = 0; i < BACKGROUND_NUMBER && ret == true; i++) {
		if (background_graphics[i] == nullptr)
			ret = false;
	}
	image_index = 0.0f;
	speed = 0.0037f;
	return ret;
}

update_status ModuleSceneWelcome::PreUpdate() {
	return UPDATE_CONTINUE;
}

update_status ModuleSceneWelcome::Update() {
	bool ret = false;
	image_index += speed;
	if (image_index > BACKGROUND_NUMBER)
		image_index = 0.0f;
	
	ret = App->render->Blit(background_graphics[(int)image_index], 0, 0, nullptr, 0.0f);

	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
}

update_status ModuleSceneWelcome::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleSceneWelcome::CleanUp() {
	bool ret = true;
	for (int i = 0; i < BACKGROUND_NUMBER && ret == true; i++) {
		ret = App->textures->Unload(background_graphics[i]);
	}
	return ret;
}