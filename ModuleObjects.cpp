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
#include "SDL/include/SDL_timer.h"
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

	//Final door animation
	final_door.PushBack({860, 0, 88, 43});
	final_door.PushBack({ 962, 0, 87, 57 });
	final_door.PushBack({ 962, 83, 96, 59 });
	final_door.speed = 0.1f;
	final_door.loop =false ;

	

	//Rock animation
	rock.PushBack({ 825,83,28,11 });

	//Rock after bridge 
	rock2.PushBack({358, 0, 31, 17});

	//box
	box.PushBack({535, 0, 20, 16});
	box.PushBack({535, 24, 20, 16});
	box.speed = 0.04f;


	//box side of the canon
	box2.PushBack({471, 0, 21, 16});
	box2.PushBack({ 494 ,0, 21, 16 });
	box2.speed = 0.04f;

	//box individual
	box3.PushBack({ 424, 0, 11, 10 });
	box3.PushBack({ 439 ,0, 11, 10});
	box3.speed = 0.04f;



	helix1.PushBack({ 785, 419, 96, 33 }, { 92, 0 });
	helix1.PushBack({ 875, 459, 96, 33 }, { 2, 0 });
	helix1.PushBack({ 800, 553, 79, 21 }, { 77,21 });
	helix1.PushBack({ 857, 503, 42, 45 }, { 20,0 });
	helix1.PushBack({ 865, 588, 26, 27 }, { 12, 27 });
	helix1.PushBack({ 877, 393, 79, 21 }, { 0, 21 });
	
	helix1.loop = true;
	helix1.speed = 0.25f;
	
	helicopter1.PushBack({ 710,440,64,82 }, { 31,0 });

	helicopter2.PushBack({ 714,658,56,69 }, { 27,0 });

	helicopter3.PushBack({ 799,914,48,55 }, { 23,0 });

	
	helix2.PushBack({ 861, 648, 32, 33 }, { 16,0 });
	helix2.PushBack({ 868, 697, 20, 20 }, { 9,20 });
	helix2.PushBack({ 875, 725, 65, 19 }, { 2,16 });
	helix2.PushBack({ 798, 765, 86, 28 }, { 79,0 });
	helix2.PushBack({ 872, 803, 86, 28 }, { 4,0 });
	helix2.PushBack({ 814, 845, 65, 20 }, { 61,16 });
	helix2.speed = 0.25f;
	helix2.loop = true;


	helix3.PushBack({ 870, 900, 16, 17 });
	helix3.PushBack({ 866, 926, 24, 28 });
	helix3.PushBack({ 876, 963, 53, 15 });
	helix3.PushBack({ 811, 991, 71, 24 });
	helix3.PushBack({ 873, 1020, 71, 24 });
	helix3.PushBack({ 827, 1044, 53, 15 });
	helix3.speed = 0.25f;
	helix3.loop = true;




	return true;


}

bool ModuleObjects::Start() {
	bool ret = true;
	sprite_graphics = App->textures->Load("Images/sprites.png");
	level_dimensions = App->scene_game->getLevelDimensions(); //This is the lower limit of the level (y)

	helipoint.x = (SCREEN_WIDTH / 2) + 20;
	helipoint.y = 1908;
	reduction = 1;
	helicopter = &helicopter1;
	helix = &helix1;


	if (App->scene_game->getLevel() == 1)
	{
		// Collisions of the rock at the upper left corner at the beggining of the game
		App->collision->AddCollider({ 20, 10 + level_dimensions.y, 10, 17 }, COLLIDER_WALL);
		App->collision->AddCollider({ 30, 13 + level_dimensions.y, 2, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 32, 18 + level_dimensions.y, 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 37, 22 + level_dimensions.y, 3, 2 }, COLLIDER_WALL);
		//App->collision->AddCollider({ 42, 22 + level_dimensions.y , 4, 3 }, COLLIDER_WALL);

		// Palm trees collisions
		App->collision->AddCollider({ 218, 152 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 170, -24 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 144, -24 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		//App->collision->AddCollider({ 160, -40 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 42, -217 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 154, -233 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 32, -233 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 154, -618 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 32, -618 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 97, -681 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 98, 24 + level_dimensions.y , 4, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 97, -106 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 97, -298 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 160, -361 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 225, -425 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 34, 152 + level_dimensions.y , 4, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 161, 217 + level_dimensions.y , 4, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 170, 233 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 145, 233 + level_dimensions.y , 4, 9 }, COLLIDER_WALL);

		//Collisions of the rock at the right at the beggining of the game
		App->collision->AddCollider({ 199, 74 + level_dimensions.y , 45, 20 }, COLLIDER_WALL);
		App->collision->AddCollider({ 204, 70 + level_dimensions.y , 35, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 207, 66 + level_dimensions.y , 33, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 217, 64 + level_dimensions.y , 24, 2 }, COLLIDER_WALL);

		//Collisions of the 2nd rock at the right 
		App->collision->AddCollider({ 204, -148 + level_dimensions.y , 48, 28 }, COLLIDER_WALL);
		App->collision->AddCollider({ 210, -158 + level_dimensions.y , 40, 10 }, COLLIDER_WALL);
		App->collision->AddCollider({ 214, -163 + level_dimensions.y , 40, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 224, -168 + level_dimensions.y , 30, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 230, -173 + level_dimensions.y , 20, 5 }, COLLIDER_WALL);

		//Collisions of the rock at the middle of the before the bridge 
		App->collision->AddCollider({ 99, -477 + level_dimensions.y , 47, 8 }, COLLIDER_WALL);
		App->collision->AddCollider({ 87, -477 + level_dimensions.y , 12, 1 }, COLLIDER_WALL);
		//App->collision->AddCollider({ 146, -477 + level_dimensions.y , 17, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 91, -487 + level_dimensions.y , 73, 10 }, COLLIDER_WALL);
		App->collision->AddCollider({ 96, -492 + level_dimensions.y , 63, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 99, -495 + level_dimensions.y , 55, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 114, -500 + level_dimensions.y , 38, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 120, -504 + level_dimensions.y , 29, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 128, -507 + level_dimensions.y , 15, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 133, -510 + level_dimensions.y , 7, 3 }, COLLIDER_WALL);

		//Collisions of the big rock at the left before the bridge
		App->collision->AddCollider({ 20, -438 + level_dimensions.y , 26, 65 }, COLLIDER_WALL);
		App->collision->AddCollider({ 46, -435 + level_dimensions.y , 9, 54 }, COLLIDER_WALL);
		App->collision->AddCollider({ 55, -423 + level_dimensions.y , 17 ,27 }, COLLIDER_WALL);
		App->collision->AddCollider({ 55, -428 + level_dimensions.y , 11 ,5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, -442 + level_dimensions.y , 24, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, -446 + level_dimensions.y , 6, 4 }, COLLIDER_WALL);

		//Collisions of the bridge
		App->collision->AddCollider({ 20, -850 + level_dimensions.y , 78, 60 }, COLLIDER_WALL);
		App->collision->AddCollider({ 159, -850 + level_dimensions.y , 80 ,60 }, COLLIDER_WALL);

		//Collisions for the lake
		App->collision->AddCollider({ 20, -171 + level_dimensions.y , 16, 1 }, COLLIDER_WATER);

		//Collisions for the bunkers
		App->collision->AddCollider({ 134, -289 + level_dimensions.y , 48, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 198, -738 + level_dimensions.y , 52, 5 }, COLLIDER_WALL);

		//Collisions of the trees and lake of the left down corner
		App->collision->AddCollider({ 20, 213 + level_dimensions.y , 66, 25 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, 238 + level_dimensions.y , 66, 18 }, COLLIDER_WATER);
		App->collision->AddCollider({ 20, 210 + level_dimensions.y , 65, 3 }, COLLIDER_WALL);
		//App->collision->AddCollider({34, 208 + level_dimensions.y ,  43, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 37, 200 + level_dimensions.y , 36, 10 }, COLLIDER_WALL);
		//App->collision->AddCollider({ 34, 199 + level_dimensions.y , 38, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 44, 196 + level_dimensions.y , 26, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 48, 194 + level_dimensions.y , 20, 2 }, COLLIDER_WALL);


		//Collisions of the rocks after the bridge
		App->collision->AddCollider({ 17, 710, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 65, 646, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 113, 742, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 225, 678, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 161, 613, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 17, 517, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 112, 517, 28, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 209, 517, 28, 3 }, COLLIDER_WALL);
		

		//Collisions for thetrinches after the bridge
		App->collision->AddCollider({ 0, 418, 59, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({130, 448, 89, 6 }, COLLIDER_WALL);
		App->collision->AddCollider({ 100, 320, 51, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 6, 290, 83, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 197, 225, 50, 3 }, COLLIDER_WALL);


		//Colliders for the final door
		App->collision->AddCollider({ 0, 0, 87, 25 }, COLLIDER_WALL);
		App->collision->AddCollider({ 170, 0, 86, 25 }, COLLIDER_WALL);

		//Colliders for the boxes
		App->collision->AddCollider({ 148, 1336, 20, 16 }, COLLIDER_BOX);
		App->collision->AddCollider({ 140, 430, 20, 16 }, COLLIDER_BOX);
		App->collision->AddCollider({ 30, 274,	 20, 16 }, COLLIDER_BOX);
		
		App->collision->AddCollider({ 195, 900, 21, 17 }, COLLIDER_BOX);
		App->collision->AddCollider({ 200, 212, 11, 10 }, COLLIDER_BOX);
	}


	if (sprite_graphics == nullptr)
		ret = false;


	return ret;
}



update_status ModuleObjects::Update() {
	if (App->scene_game->getLevel() == 1)
	{
		App->render->Blit(sprite_graphics, 208, 128 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 19, 128 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 83, 0 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		//Group of three palms
		App->render->Blit(sprite_graphics, 146, 193 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 160, 209 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 130, 209 + level_dimensions.y , &tree1.GetCurrentFrame().rect);

		//Groups of three palms
		App->render->Blit(sprite_graphics, 130, -49 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 160, -49 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 146, -65 + level_dimensions.y , &tree1.GetCurrentFrame().rect);

		//Group of three palms
		App->render->Blit(sprite_graphics, 1, -240 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 32, -240 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 17, -256 + level_dimensions.y , &tree1.GetCurrentFrame().rect);

		App->render->Blit(sprite_graphics, 82, -129 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 82, -320 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 144, -257 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 146, -385 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 210, -449 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 144, -642 + level_dimensions.y , &tree2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 18, -642 + level_dimensions.y , &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 82, -706 + level_dimensions.y , &tree1.GetCurrentFrame().rect);

	
		//Rocks sprites
		App->render->Blit(sprite_graphics, 112, -925, &rock.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 15, -957, &rock.GetCurrentFrame().rect);

		//Rock after bridge
		App->render->Blit(sprite_graphics, 15, 696, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 112, 728, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 224, 663, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 64, 632, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 160, 600, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 16, 503, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 111, 503, &rock2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 208, 503, &rock2.GetCurrentFrame().rect);


		//Boxes
		App->render->Blit(sprite_graphics, 148, 1336, &box.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 195, 900, &box2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 140, 430, &box.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 200, 212, &box3.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 30, 274, &box.GetCurrentFrame().rect);
		
		if (App->player->position.y <= 234)
		{
			App->render->Blit(sprite_graphics, 81, 0, &final_door.GetCurrentFrame().rect);
		}

		if (App->scene_game->intro == true)
		{
			helix->speed = 0.5f;
			if (droping == false)
			{
				
				if (helipoint.y > 1780)
				{
					helipoint.y = helipoint.y - 1;
					helicopter->speed = 0;
					timer = SDL_GetTicks();
				}
				else if (helipoint.y <= 1780 && helipoint.y != helipoint.y - reduction)
				{

						helipoint.y = helipoint.y - reduction;
						reduction = reduction - 0.01f;
						if (SDL_GetTicks() - 4500 <= timer)
						{
							helicopter = &helicopter2;
							helix = &helix2;
							timer = SDL_GetTicks();
							tree1.speed = 0.02f;
							tree2.speed = 0.02f;
						}
					
				}
				else if (SDL_GetTicks() - 1000 <= timer)
				{

					helicopter = &helicopter3;
					tree1.speed = 0.035f;
					tree2.speed = 0.035f;			
				}
				else if (SDL_GetTicks() - 6000 <= timer)
				{
					droping = true;
					timer = SDL_GetTicks();
				}
			}
			else if (helipoint.y >= 1708 - SCREEN_HEIGHT - 82)
			{
	
				if (SDL_GetTicks() - 1000 <= timer)
				{
					helicopter = &helicopter2;
					tree1.speed = 0.02f;
					tree2.speed = 0.02f;
			
				}
				else if (SDL_GetTicks() - 1200 <= timer)
				{
					helicopter = &helicopter1;
					tree1.speed = 0;
					tree2.speed = 0;
				}
			
					helipoint.y = helipoint.y - reduction;
					reduction = reduction + 0.01f;
			
				
			}
			AnimationFrame frame = helicopter->GetCurrentFrame();
			AnimationFrame helixfr = helix->GetCurrentFrame();
			iPoint pivot = frame.pivot;
			iPoint pivot2 = helixfr.pivot;
			App->render->Blit(sprite_graphics, helipoint.x - pivot.x, helipoint.y - pivot.y, &frame.rect);
			App->render->Blit(sprite_graphics, helipoint.x - pivot2.x, helipoint.y  - pivot2.y, &helixfr.rect);
		}
					
		
		}

	

	return update_status::UPDATE_CONTINUE;
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

