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
#include "ModuleEnemies.h"
#include <string>


ModuleSceneGame::ModuleSceneGame()
{
}


ModuleSceneGame::~ModuleSceneGame()
{
}

bool ModuleSceneGame::Init() {
	level = 1;
	//Tree left
	tree1.PushBack({ 219, 0, 31, 32 });
	tree1.PushBack({ 251, 0, 30, 32 });
	tree1.speed = 0.0f;

	//Tree right
	tree2.PushBack({ 178,46,31,32 });
	tree2.PushBack({ 209,46,30,32 });
	tree2.speed = 0.0f;

	//Rock animation
	rock.PushBack({ 825,83,28,11 });
	return true;
}

bool ModuleSceneGame::Start() {
	bool ret = true;
	std::string str = "Images/Mapa";
	str.append(std::to_string(level));
	str.append(".png");
	background_graphics = App->textures->Load(str.c_str(), &level_dimensions);
	App->render->camera.x = -20 * SCREEN_SIZE;
	App->render->camera.y = (-level_dimensions.y + SCREEN_HEIGHT) * SCREEN_SIZE;
	//App->render->camera.y = (-level_dimensions.y + SCREEN_HEIGHT) * SCREEN_SIZE;

	// Collisions of the rock at the left  upcorner at the beggining of the game
	App->collision->AddCollider({ 20, 8, 10, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 30, 11, 2, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 32, 16, 5, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 37, 20, 5, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 42, 20, 4, 8 }, COLLIDER_WALL);

	// Palm trees collisions
	App->collision->AddCollider({ 218, 152, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 170, -24, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 144, -24, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, -40, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 42, -217, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 154, -233, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 32, -233, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 154, -618, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 32, -618, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 97, -681, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 98, 24, 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 97, -106, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 97, -298, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, -361 , 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 225, -425 , 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 34, 152, 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 161, 217, 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 170, 233, 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, 233, 4, 9 }, COLLIDER_WALL);

	//Collisions of the rock at the right at the beggining of the game
	App->collision->AddCollider({ 196, 74 , 45, 23 }, COLLIDER_WALL);
	App->collision->AddCollider({ 201, 70 , 35, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 204, 66 , 33, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 214, 64 , 24, 2 }, COLLIDER_WALL);

	//Collisions of the 2nd rock at the right 
	App->collision->AddCollider({ 196, -151 , 48, 38 }, COLLIDER_WALL);
	App->collision->AddCollider({ 203, -166 , 40, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 215, -173 , 40, 7 }, COLLIDER_WALL);

	//Collisions of the rock at the middle of the before the briedge 
	App->collision->AddCollider({ 84, -482 , 87, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 89, -497 , 80, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 114, -505 , 41, 8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 126, -511 , 24, 6 }, COLLIDER_WALL);

	//Collisions of the big rock at the left before the briedge
	App->collision->AddCollider({ 20, -448 , 35, 80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 55, -438 , 22 ,50 }, COLLIDER_WALL);

	//Collisions of the briedge
	App->collision->AddCollider({ 20, -850 , 78, 78 }, COLLIDER_WALL);
	App->collision->AddCollider({ 159, -850 , 80 ,78 }, COLLIDER_WALL);
	
	//Collisions for the lake
	App->collision->AddCollider({ 20, -173 , 25, 27 }, COLLIDER_WALL);

	//Collisions for the bukers
	App->collision->AddCollider({ 128, -289 , 60, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 192, -738 , 52, 10 }, COLLIDER_WALL);

	//Collisions of the trees and lake of the left down corner
	App->collision->AddCollider({ 20, 213, 76, 43 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 210, 71, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 208,  68, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 201, 59, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 199, 58, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 192, 56, 7 }, COLLIDER_WALL);


	sprite_graphics = App->textures->Load("Images/sprites.png");

	//Enabling modules
	App->player->Enable();
	App->enemies->Enable();
	App->collision->Enable();

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
	ret = App->render->Blit(background_graphics, 0, 0, nullptr);

	App->render->Blit(sprite_graphics, 208, 128, &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 19, 128, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 83, 0, &tree1.GetCurrentFrame().rect);
	//Group of three palms
	App->render->Blit(sprite_graphics, 146, 193, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 160, 209, &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 130, 209, &tree1.GetCurrentFrame().rect);
	
	//Groups of three palms
	App->render->Blit(sprite_graphics, 130, -49, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 160, -49, &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 146, -65, &tree1.GetCurrentFrame().rect);
	//Group of three palms
	App->render->Blit(sprite_graphics, 1, -240, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 32, -240, &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 17, -256, &tree1.GetCurrentFrame().rect);

	App->render->Blit(sprite_graphics, 82, -129, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 82, -320, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 144, -257, &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 146, -385, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 210, -449 , &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 144, -642, &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 18, -642, &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 82, -706, &tree1.GetCurrentFrame().rect);

	//Rocks sprites
	App->render->Blit(sprite_graphics, 112, -925, &rock.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 15, -957, &rock.GetCurrentFrame().rect);

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
	App->collision->Disable();
	
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