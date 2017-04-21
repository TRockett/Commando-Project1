#include "ModuleObjects.h"
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


ModuleObjects::ModuleObjects()
{
}


ModuleObjects::~ModuleObjects()
{
}



bool ModuleObjects::Init() {
	
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

	//Rock after bridge 
	rock2.PushBack({358, 0, 31, 17});
	return true;


}

bool ModuleObjects::Start() {
	bool ret = true;
	sprite_graphics = App->textures->Load("Images/sprites.png");
	level_dimensions = App->scene_game->level_dimensions;

	// Collisions of the rock at the upper left corner at the beggining of the game
	App->collision->AddCollider({ 20, 8 - (-level_dimensions.y + SCREEN_HEIGHT), 10, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 30, 11 - (-level_dimensions.y + SCREEN_HEIGHT), 2, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 32, 16 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 37, 20 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 42, 20 - (-level_dimensions.y + SCREEN_HEIGHT), 4, 8 }, COLLIDER_WALL);

	// Palm trees collisions
	App->collision->AddCollider({ 218, 152 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 170, -24 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 144, -24 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, -40 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 42, -217 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 154, -233 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 32, -233 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 154, -618 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 32, -618 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 97, -681 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 98, 24 - (-level_dimensions.y + SCREEN_HEIGHT), 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 97, -106 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 97, -298 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, -361 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 225, -425 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 34, 152 - (-level_dimensions.y + SCREEN_HEIGHT), 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 161, 217 - (-level_dimensions.y + SCREEN_HEIGHT), 4, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 170, 233 - (-level_dimensions.y + SCREEN_HEIGHT), 5, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, 233 - (-level_dimensions.y + SCREEN_HEIGHT), 4, 9 }, COLLIDER_WALL);

	//Collisions of the rock at the right at the beggining of the game
	App->collision->AddCollider({ 196, 74 - (-level_dimensions.y + SCREEN_HEIGHT), 45, 23 }, COLLIDER_WALL);
	App->collision->AddCollider({ 201, 70 - (-level_dimensions.y + SCREEN_HEIGHT), 35, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 204, 66 - (-level_dimensions.y + SCREEN_HEIGHT), 33, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 214, 64 - (-level_dimensions.y + SCREEN_HEIGHT), 24, 2 }, COLLIDER_WALL);

	//Collisions of the 2nd rock at the right 
	App->collision->AddCollider({ 196, -151 - (-level_dimensions.y + SCREEN_HEIGHT), 48, 38 }, COLLIDER_WALL);
	App->collision->AddCollider({ 203, -166 - (-level_dimensions.y + SCREEN_HEIGHT), 40, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 215, -173 - (-level_dimensions.y + SCREEN_HEIGHT), 40, 7 }, COLLIDER_WALL);

	//Collisions of the rock at the middle of the before the bridge 
	App->collision->AddCollider({ 84, -482 - (-level_dimensions.y + SCREEN_HEIGHT), 87, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 89, -497 - (-level_dimensions.y + SCREEN_HEIGHT), 80, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 114, -505 - (-level_dimensions.y + SCREEN_HEIGHT), 41, 8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 126, -511 - (-level_dimensions.y + SCREEN_HEIGHT), 24, 6 }, COLLIDER_WALL);

	//Collisions of the big rock at the left before the bridge
	App->collision->AddCollider({ 20, -448 - (-level_dimensions.y + SCREEN_HEIGHT), 35, 80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 55, -438 - (-level_dimensions.y + SCREEN_HEIGHT), 22 ,50 }, COLLIDER_WALL);

	//Collisions of the bridge
	App->collision->AddCollider({ 20, -850 - (-level_dimensions.y + SCREEN_HEIGHT), 78, 78 }, COLLIDER_WALL);
	App->collision->AddCollider({ 159, -850 - (-level_dimensions.y + SCREEN_HEIGHT), 80 ,78 }, COLLIDER_WALL);

	//Collisions for the lake
	App->collision->AddCollider({ 20, -171 - (-level_dimensions.y + SCREEN_HEIGHT), 16, 1 }, COLLIDER_WATER);

	//Collisions for the bunkers
	App->collision->AddCollider({ 128, -289 - (-level_dimensions.y + SCREEN_HEIGHT), 60, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 192, -738 - (-level_dimensions.y + SCREEN_HEIGHT), 52, 10 }, COLLIDER_WALL);

	//Collisions of the trees and lake of the left down corner
	App->collision->AddCollider({ 20, 213 - (-level_dimensions.y + SCREEN_HEIGHT), 66, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 238 - (-level_dimensions.y + SCREEN_HEIGHT), 66, 18 }, COLLIDER_WATER);
	App->collision->AddCollider({ 20, 210 - (-level_dimensions.y + SCREEN_HEIGHT), 65, 3 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 208 - (-level_dimensions.y + SCREEN_HEIGHT),  63, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 201 - (-level_dimensions.y + SCREEN_HEIGHT), 59, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 199 - (-level_dimensions.y + SCREEN_HEIGHT), 58, 2 }, COLLIDER_WALL);
	App->collision->AddCollider({ 20, 192 - (-level_dimensions.y + SCREEN_HEIGHT), 56, 7 }, COLLIDER_WALL);

	//Collisions of the rocks after the bridge

	//App->collision->AddCollider({18,-708});



	if (sprite_graphics == nullptr)
		ret = false;


	return ret;
}



update_status ModuleObjects::Update() {
	bool ret = true;

	App->render->Blit(sprite_graphics, 208, 128 - (-level_dimensions.y + SCREEN_HEIGHT), &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 19, 128 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 83, 0 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);
	//Group of three palms
	App->render->Blit(sprite_graphics, 146, 193 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 160, 209 - (-level_dimensions.y + SCREEN_HEIGHT), &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 130, 209 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);

	//Groups of three palms
	App->render->Blit(sprite_graphics, 130, -49 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 160, -49 - (-level_dimensions.y + SCREEN_HEIGHT), &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 146, -65 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);

	//Group of three palms
	App->render->Blit(sprite_graphics, 1, -240 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 32, -240 - (-level_dimensions.y + SCREEN_HEIGHT), &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 17, -256 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);

	App->render->Blit(sprite_graphics, 82, -129 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 82, -320 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 144, -257 - (-level_dimensions.y + SCREEN_HEIGHT), &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 146, -385 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 210, -449 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 144, -642 - (-level_dimensions.y + SCREEN_HEIGHT), &tree2.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 18, -642 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 82, -706 - (-level_dimensions.y + SCREEN_HEIGHT), &tree1.GetCurrentFrame().rect);

	//Rocks sprites
	App->render->Blit(sprite_graphics, 112, -925 , &rock.GetCurrentFrame().rect);
	App->render->Blit(sprite_graphics, 15, -957, &rock.GetCurrentFrame().rect);

	//Rock after bridge

	App->render->Blit(sprite_graphics, 15, 696, &rock2.GetCurrentFrame().rect);

	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
}

update_status ModuleObjects::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleObjects::CleanUp() {
	bool ret = true;
	
	
	App->collision->Disable();
	App->enemies->Disable();

	ret = App->textures->Unload(sprite_graphics);

	

	return ret;
}

