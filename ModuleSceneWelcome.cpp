#include "ModuleSceneWelcome.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneGame.h"
#include "ModuleSound.h"


ModuleSceneWelcome::ModuleSceneWelcome()
{
}


ModuleSceneWelcome::~ModuleSceneWelcome()
{
}


bool ModuleSceneWelcome::Init() {
	
	background_graphics = nullptr;
	welcome_anim.speed = 0.0037f;
	welcome_anim.PushBack({ 20,150,216,256 });
	welcome_anim.PushBack({ 20,1800,216,256 });
	welcome_anim.PushBack({ 20,0,216,256 });


	return true;
}

bool ModuleSceneWelcome::Start() {
	bool ret = true;

	background_graphics = App->textures->Load("Images/Mapa4.png");
	title_graphics = App->textures->Load("Images/title.png");
	if (background_graphics == nullptr)
		ret = false;
	if (title_graphics == nullptr)
		ret = false;

	return ret;
}

update_status ModuleSceneWelcome::PreUpdate() {
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		App->fade->FadeToBlack(this, App->scene_game, 3.0f);
	return UPDATE_CONTINUE;
}

update_status ModuleSceneWelcome::Update() {
	bool ret = false;
		
	ret = App->render->Blit(background_graphics, 0, 0, &welcome_anim.GetCurrentFrame(), 0.0f);
	if (welcome_anim.getFrameIndex() != 0)
		App->render->Blit(title_graphics, 10, 56, nullptr, 0);

	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
}

update_status ModuleSceneWelcome::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleSceneWelcome::CleanUp() {
	bool ret = true;
	
	ret = App->textures->Unload(background_graphics);
	if (!App->textures->Unload(title_graphics))
		ret = false;
	return ret;
}