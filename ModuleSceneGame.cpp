#include "ModuleSceneGame.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneCongrats.h"
#include "ModuleSound.h"
#include "ModuleCollision.h"
#include <string>


ModuleSceneGame::ModuleSceneGame()
{
}


ModuleSceneGame::~ModuleSceneGame()
{
}

bool ModuleSceneGame::Init() {
	level = 1;
	tree1.PushBack({ 219, 0, 31, 32 });
	tree1.PushBack({ 251, 0, 30, 32 });
	tree1.speed = 0.05f;
	return true;
}

bool ModuleSceneGame::Start() {
	bool ret = true;
	std::string str = "Images/Mapa";
	str.append(std::to_string(level));
	str.append(".png");
	background_graphics = App->textures->Load(str.c_str(), &level_dimensions);
	App->render->camera.x = -20 * SCREEN_SIZE;
	//App->render->camera.y = (-level_dimensions.y + SCREEN_HEIGHT) * SCREEN_SIZE;
	
	// Collisions of the rock at the left  upcorner at the beggining of the game
	App->collision->AddCollider({ 20, 8, 10, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 30, 11, 2, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 32, 16, 5, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 37, 20, 5, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 42, 20, 4, 8 }, COLLIDER_WALL);

	// Palm trees collisions
	App->collision->AddCollider({ 218, 152, 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 98, 24, 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 34, 152, 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 161, 217, 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 170, 233, 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, 233, 4, 9 }, COLLIDER_WALL);

	//Collisions of the rock at the right at the beggining of the game
	App->collision->AddCollider({ 196, 74 , 45, 23 }, COLLIDER_WALL);
	App->collision->AddCollider({ 201, 70 , 35, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 204, 66 , 33, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 214, 64 , 24, 2 }, COLLIDER_WALL);

	//Collisions of the trees and lake of the left down corner
	App->collision->AddCollider({ 20, 213, 76, 43 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 210, 71, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 208,  68, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 201, 59, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 199, 58, 2 }, COLLIDER_WALL);



	sprite_graphics = App->textures->Load("Images/sprites.png");

	App->player->Enable();
	if (background_graphics == nullptr)
		ret = false;
	
	if (sprite_graphics == nullptr)
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
				App->collision->Disable();
			}
		}
		else {
			if (App->fade->FadeToBlack(this, this, 1.0f)) {
				level++;
				App->collision->Disable();
			}
		}
	}
	return UPDATE_CONTINUE;
}

update_status ModuleSceneGame::Update() {
	bool ret = true;
	ret = App->render->Blit(background_graphics, 0, -level_dimensions.y + SCREEN_HEIGHT, nullptr);
	App->render->Blit(sprite_graphics, 203, 128, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 19, 128, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 146, 193, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 155, 209, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 130, 209, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 83, 0, &tree1.GetCurrentFrame().rect);


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
	App->player->Disable();
	
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