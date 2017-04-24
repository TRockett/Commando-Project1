#include "ModuleInterface.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"


ModuleInterface::ModuleInterface()
{
}


ModuleInterface::~ModuleInterface()
{
}


bool ModuleInterface::Init() {

	graphics = nullptr;

	return true;
}

bool ModuleInterface::Start() {
	bool ret = true;

	graphics = App->textures->Load("Images/sprites.png");

	if (graphics == nullptr)
		ret = false;
	
	return ret;
}
//
//update_status ModuleInterface::PreUpdate() {
//	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
//		App->fade->FadeToBlack(this, App->scene_game, 3.0f);
//	return UPDATE_CONTINUE;
//}
//
//update_status ModuleSceneWelcome::Update() {
//	bool ret = false;
//	AnimationFrame frame = welcome_anim.GetCurrentFrame();
//	ret = App->render->Blit(background_graphics, 0 + frame.pivot.x, 0 + frame.pivot.y, &frame.rect, 0.0f);
//	if (welcome_anim.getFrameIndex() == 0)
//	{
//		App->render->Blit(screen_welcome, 0, 70, &screen_1.GetCurrentFrame().rect);
//
//	}
//	if (welcome_anim.getFrameIndex() != 0)
//		App->render->Blit(title_graphics, 10, 56, nullptr, 0);
//
//	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
//}
//
//update_status ModuleSceneWelcome::PostUpdate() {
//	return UPDATE_CONTINUE;
//}
//
//bool ModuleSceneWelcome::CleanUp() {
//	bool ret = true;
//
//	ret = App->textures->Unload(background_graphics);
//	if (!App->textures->Unload(title_graphics))
//		ret = false;
//	return ret;
//}