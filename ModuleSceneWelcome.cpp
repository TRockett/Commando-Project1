
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

	screen_welcome = nullptr;
	screen_1.speed = 0.05f;
	screen_1.PushBack({ 0, 0, 224, 182 });
	screen_1.PushBack({ 252, 0, 224, 182 });
	screen_1.PushBack({ 0, 203, 224, 182 });

	return true;
}

bool ModuleSceneWelcome::Start() {
	bool ret = true;

	background_graphics = App->textures->Load("Images/Mapa4.png");
	title_graphics = App->textures->Load("Images/title.png");
	screen_welcome = App->textures->Load("Images/screen1.png");
	capcom = App->textures->Load("Images/capcom.png");

	if (background_graphics == nullptr)
		ret = false;
	if (title_graphics == nullptr)
		ret = false;
	if (screen_welcome == nullptr)
		ret = false;
	if (capcom == nullptr)
		ret = false;
	return ret;
}

update_status ModuleSceneWelcome::PreUpdate() {
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
		App->fade->FadeToBlack(this, App->scene_game, 3.0f);
	return UPDATE_CONTINUE;
}

update_status ModuleSceneWelcome::Update() {
	bool ret = false;
	AnimationFrame frame = welcome_anim.GetCurrentFrame();
	ret = App->render->Blit(background_graphics, 0 + frame.pivot.x, 0 + frame.pivot.y, &frame.rect, 0.0f);

	if (welcome_anim.getFrameIndex() == 0) 
	{
		App->render->Blit(screen_welcome, -4, 70, &screen_1.GetCurrentFrame().rect);

	}
	if (welcome_anim.getFrameIndex() != 0)
		App->render->Blit(title_graphics, 8, 56, nullptr, 0);
		App->render->Blit(capcom, 29, SCREEN_HEIGHT- 36, nullptr, 0);

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
	if (!App->textures->Unload(capcom))
		ret = false;
	if (!App->textures->Unload(screen_welcome))
		ret = false;
	return ret;
}