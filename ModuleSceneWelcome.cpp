#include "ModuleSceneWelcome.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"


ModuleSceneWelcome::ModuleSceneWelcome()
{
}


ModuleSceneWelcome::~ModuleSceneWelcome()
{
}


bool ModuleSceneWelcome::Init() {
	
	background_graphics = nullptr;
	welcome_anim.speed = 0.0037f;
	welcome_anim.PushBack({ 0,150,189,216 });
	welcome_anim.PushBack({ 0,1589,189,216 });
	welcome_anim.PushBack({ 0,0,189,216 });


	return true;
}

bool ModuleSceneWelcome::Start() {
	background_graphics = App->textures->Load("Images/Mapa4.png");
	bool ret = true;
	
	if (background_graphics == nullptr)
		ret = false;

	return ret;
}

update_status ModuleSceneWelcome::PreUpdate() {
	//if(App->input->keyboard[SDL_SCANCODE_PAGEUP] == 1)
		//App->fade->FadeToBlack(this, App->)
	return UPDATE_CONTINUE;
}

update_status ModuleSceneWelcome::Update() {
	bool ret = false;
		
	ret = App->render->Blit(background_graphics, 0, 0, &welcome_anim.GetCurrentFrame(), 0.0f);

	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
}

update_status ModuleSceneWelcome::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleSceneWelcome::CleanUp() {
	bool ret = true;
	
	ret = App->textures->Unload(background_graphics);
	return ret;
}