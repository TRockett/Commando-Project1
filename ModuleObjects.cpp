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
#include "ModuleLevel3.h"


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
	final_door.speed = 0;
	final_door.loop =false ;

	//Door of the bunkers of level 3 animation but left side
	door_bunker_left.PushBack({ 596,196,12, 23 });
	door_bunker_left.PushBack({ 580,196,12, 22 });
	door_bunker_left.PushBack({ 564,196,12, 20 });
	door_bunker_left.PushBack({ 548,196,12, 18 });
	door_bunker_left.PushBack({ 532,196,12, 16 });
	door_bunker_left.PushBack({ 516,196,12, 14 });
	door_bunker_left.PushBack({ 500,196,12, 12 });
	door_bunker_left.PushBack({ 484,196,12, 10 });
	door_bunker_left.PushBack({ 468,196,12, 8 });
	door_bunker_left.PushBack({ 453,196,12, 6 });
	door_bunker_left.PushBack({ 468,196,12, 8 });
	door_bunker_left.PushBack({ 484,196,12, 10 });
	door_bunker_left.PushBack({ 500,196,12, 12 });
	door_bunker_left.PushBack({ 516,196,12, 14 });
	door_bunker_left.PushBack({ 532,196,12, 16 });
	door_bunker_left.PushBack({ 548,196,12, 18 });
	door_bunker_left.PushBack({ 564,196,12, 20 });
	door_bunker_left.PushBack({ 580,196,12, 22 });
	door_bunker_left.PushBack({ 596,196,12, 23 });
	door_bunker_left.loop = false;
	door_bunker_left.speed = 0.2f;

	//Door of the bunkers of level 3 animation
	door_bunker.PushBack({630,196,12, 23});
	door_bunker.PushBack({ 646,196,12, 22 });
	door_bunker.PushBack({ 662,196,12, 20 });
	door_bunker.PushBack({ 678,196,12, 18 });
	door_bunker.PushBack({ 694,196,12, 16 });
	door_bunker.PushBack({ 710,196,12, 14 });
	door_bunker.PushBack({ 726,196,12, 12 });
	door_bunker.PushBack({ 742,196,12, 10 });
	door_bunker.PushBack({ 758,196,12, 8 });
	door_bunker.PushBack({ 773,196,12, 6 });
	door_bunker.PushBack({ 758,196,12, 8 });
	door_bunker.PushBack({ 742,196,12, 10 });
	door_bunker.PushBack({ 726,196,12, 12 });
	door_bunker.PushBack({ 710,196,12, 14 });
	door_bunker.PushBack({ 694,196,12, 16 });
	door_bunker.PushBack({ 678,196,12, 18 });
	door_bunker.PushBack({ 662,196,12, 20 });
	door_bunker.PushBack({ 646,196,12, 22 });
	door_bunker.PushBack({ 630,196,12, 23 });
	door_bunker.loop = false;
	door_bunker.speed = 0.5f;
	door_bunker1 = door_bunker;
	door_bunker2 = door_bunker;
	door_bunker3 = door_bunker;
	door_bunker4 = door_bunker;
	door_bunker5 = door_bunker;
	door_bunker6 = door_bunker;
	door_bunker_left1 = door_bunker_left;
	door_bunker_left2 = door_bunker_left;
	door_bunker_left3 = door_bunker_left;

	//Bunker house of level 4 animation
	bunker_house.PushBack({ 941, 200, 12, 30 });
	bunker_house.PushBack({ 925, 200, 11, 30 });
	bunker_house.PushBack({ 910, 200, 10, 30 });
	bunker_house.PushBack({ 895, 200, 9, 30 });
	bunker_house.PushBack({ 882, 200, 8, 30 });
	bunker_house.PushBack({ 871, 200, 7, 30 });
	bunker_house.PushBack({ 860, 200, 6, 30 });
	bunker_house.PushBack({ 850, 200, 5, 30 });
	bunker_house.PushBack({ 841, 200, 4, 30 });
	bunker_house.PushBack({ 833, 200, 3, 30 });
	bunker_house.PushBack({ 826, 200, 2, 30 });
	bunker_house.PushBack({ 820, 200, 1, 30 });
	bunker_house.PushBack({ 819, 200, 1, 30 });
	bunker_house.PushBack({ 820, 200, 1, 30 });
	bunker_house.PushBack({ 826, 200, 2, 30 });
	bunker_house.PushBack({ 833, 200, 3, 30 });
	bunker_house.PushBack({ 841, 200, 4, 30 });
	bunker_house.PushBack({ 850, 200, 5, 30 });
	bunker_house.PushBack({ 860, 200, 6, 30 });
	bunker_house.PushBack({ 871, 200, 7, 30 });
	bunker_house.PushBack({ 882, 200, 8, 30 });
	bunker_house.PushBack({ 895, 200, 9, 30 });
	bunker_house.PushBack({ 910, 200, 10, 30 });
	bunker_house.PushBack({ 925, 200, 11, 30 });
	bunker_house.PushBack({ 941, 200, 12, 30 });
	bunker_house.loop = true;
	bunker_house.speed = 0.5f;


	//Trinxera
	trinxera.PushBack({353, 75, 77, 16});

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

	mortar_right1.PushBack({ 77,392,14,15 });
	mortar_right2.PushBack({ 92,392,14,16 });
	mortar_right3.PushBack({ 107,392,14,16 });
	mortar_right4.PushBack({ 121,392,14,16 });

	mortar_left1.PushBack({ 137,392,14,16 });
	mortar_left2.PushBack({ 152,392,14,16 });
	mortar_left3.PushBack({ 167,392,14,16 });
	mortar_left4.PushBack({ 182,392,14,15 });

	return true;
}

bool ModuleObjects::Start() {
	bool ret = true;
	sprite_graphics = App->textures->Load("Images/sprites.png");
	if (App->level == 1)
	{
		level_dimensions = App->scene_game->getLevelDimensions(); //This is the lower limit of the level (y)
	}
	else
	{
		level_dimensions = App->level_3->getLevelDimensions();
	}
	helipoint.x = (SCREEN_WIDTH / 2) + 20;
	helipoint.y = 1908;
	reduction = 1;
	helicopter = &helicopter1;
	helix = &helix1;


	if (App->level == 1)
	{
		// Collisions of the rock at the upper left corner at the beggining of the game
		App->collision->AddCollider({ 20, 10 + level_dimensions.y, 10, 32 }, COLLIDER_WALL);
		App->collision->AddCollider({ 30, 13 + level_dimensions.y, 2, 29 }, COLLIDER_WALL);
		App->collision->AddCollider({ 32, 18 + level_dimensions.y, 5, 20 }, COLLIDER_WALL);
		App->collision->AddCollider({ 37, 22 + level_dimensions.y, 3, 2 }, COLLIDER_WALL);
		//App->collision->AddCollider({ 42, 22 + level_dimensions.y , 4, 3 }, COLLIDER_WALL);

		// Palm trees collisions
		App->collision->AddCollider({ 218, 154 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 170, -22 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 144, -22 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);

		//App->collision->AddCollider({ 160, -40 + level_dimensions.y , 5, 9 }, COLLIDER_WALL);
		App->collision->AddCollider({ 42, -219 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 154, -235 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 32, -235 + level_dimensions.y , 5, 14}, COLLIDER_WALL);
		App->collision->AddCollider({ 154, -620 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 32, -620 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 97, -683 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 98, 26 + level_dimensions.y , 4, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 97, -108 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 97, -300 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 160, -363 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 225, -427 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 34, 154 + level_dimensions.y , 4, 14}, COLLIDER_WALL);
		App->collision->AddCollider({ 161, 219 + level_dimensions.y , 4, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 170, 235 + level_dimensions.y , 5, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 145, 235 + level_dimensions.y , 4, 14 }, COLLIDER_WALL);

		//Collisions of the rock at the right at the beggining of the game
		App->collision->AddCollider({ 199, 74 + level_dimensions.y , 45, 33 }, COLLIDER_WALL);
		App->collision->AddCollider({ 204, 70 + level_dimensions.y , 35, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 207, 66 + level_dimensions.y , 33, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 217, 64 + level_dimensions.y , 24, 2 }, COLLIDER_WALL);

		//Collisions of the 2nd rock at the right 
		App->collision->AddCollider({ 204, -148 + level_dimensions.y , 48, 48 }, COLLIDER_WALL);
		App->collision->AddCollider({ 210, -158 + level_dimensions.y , 40, 10 }, COLLIDER_WALL);
		App->collision->AddCollider({ 214, -163 + level_dimensions.y , 40, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 224, -168 + level_dimensions.y , 30, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 230, -173 + level_dimensions.y , 20, 5 }, COLLIDER_WALL);

		//Collisions of the rock at the middle of the before the bridge 
		App->collision->AddCollider({ 99, -477 + level_dimensions.y , 47, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 87, -477 + level_dimensions.y , 12, 14  }, COLLIDER_WALL);
		//App->collision->AddCollider({ 146, -477 + level_dimensions.y , 17, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 91, -487 + level_dimensions.y , 73, 20 }, COLLIDER_WALL);
		App->collision->AddCollider({ 96, -492 + level_dimensions.y , 63, 15 }, COLLIDER_WALL);
		App->collision->AddCollider({ 99, -495 + level_dimensions.y , 55, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 114, -500 + level_dimensions.y , 38, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 120, -504 + level_dimensions.y , 29, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 128, -507 + level_dimensions.y , 15, 3 }, COLLIDER_WALL);
		App->collision->AddCollider({ 133, -510 + level_dimensions.y , 7, 3 }, COLLIDER_WALL);

		//Collisions of the big rock at the left before the bridge
		App->collision->AddCollider({ 20, -438 + level_dimensions.y , 26, 80 }, COLLIDER_WALL);
		App->collision->AddCollider({ 46, -435 + level_dimensions.y , 9, 65 }, COLLIDER_WALL);
		App->collision->AddCollider({ 55, -423 + level_dimensions.y , 17 ,35 }, COLLIDER_WALL);
		App->collision->AddCollider({ 55, -428 + level_dimensions.y , 11 ,5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, -442 + level_dimensions.y , 24, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, -446 + level_dimensions.y , 6, 4 }, COLLIDER_WALL);

		//Collisions of the bridge
		App->collision->AddCollider({ 20, -850 + level_dimensions.y , 78, 77 }, COLLIDER_WALL);
		App->collision->AddCollider({ 159, -850 + level_dimensions.y , 80 ,77 }, COLLIDER_WALL);

		//Collisions for the lake
		App->collision->AddCollider({ 20, -171 + level_dimensions.y , 16, 1 }, COLLIDER_WATER);

		//Collisions for the bunkers
		App->collision->AddCollider({ 134, -277 + level_dimensions.y , 48, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 198, -725 + level_dimensions.y , 52, 2 }, COLLIDER_WALL);

		//Collisions of the trees and lake of the left down corner
		App->collision->AddCollider({ 20, 213 + level_dimensions.y , 66, 37 }, COLLIDER_WALL);
		App->collision->AddCollider({ 20, 238 + level_dimensions.y , 66, 27 }, COLLIDER_WATER);
		App->collision->AddCollider({ 20, 210 + level_dimensions.y , 65, 3 }, COLLIDER_WALL);
		//App->collision->AddCollider({34, 208 + level_dimensions.y ,  43, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 37, 200 + level_dimensions.y , 36, 10 }, COLLIDER_WALL);
		//App->collision->AddCollider({ 34, 199 + level_dimensions.y , 38, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 44, 196 + level_dimensions.y , 26, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 48, 194 + level_dimensions.y , 20, 2 }, COLLIDER_WALL);


		//Collisions of the rocks after the bridge
		App->collision->AddCollider({ 17, 710, 28, 7 }, COLLIDER_WALL);
		App->collision->AddCollider({ 65, 646, 28, 7 }, COLLIDER_WALL);
		App->collision->AddCollider({ 113, 742, 28, 7 }, COLLIDER_WALL);
		App->collision->AddCollider({ 225, 678, 28, 7 }, COLLIDER_WALL);
		App->collision->AddCollider({ 161, 613, 28, 7 }, COLLIDER_WALL);
		App->collision->AddCollider({ 17, 517, 28, 7 }, COLLIDER_WALL);
		App->collision->AddCollider({ 112, 517, 28, 7 }, COLLIDER_WALL);
		App->collision->AddCollider({ 209, 517, 28, 7 }, COLLIDER_WALL);
		

		//Collisions for thetrinches after the bridge
		App->collision->AddCollider({ 0, 430, 59, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({130, 462, 89, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 100, 334, 51, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 6, 302, 86, 2 }, COLLIDER_WALL);
		App->collision->AddCollider({ 197, 237, 53, 2 }, COLLIDER_WALL);


		//Colliders for the final door
		App->collision->AddCollider({ 0, 0, 87, 42 }, COLLIDER_WALL);
		App->collision->AddCollider({ 170, 0, 86, 42 }, COLLIDER_WALL);

		//Colliders for the boxes
		boxes[0] = App->collision->AddCollider({ 148, 1336, 20, 16 }, COLLIDER_BOX, this);
		boxes[1] = App->collision->AddCollider({ 140, 430, 20, 16 }, COLLIDER_BOX, this);
		boxes[2] = App->collision->AddCollider({ 30, 274, 20, 16 }, COLLIDER_BOX, this);
		boxes[3] = App->collision->AddCollider({ 195, 900, 21, 17 }, COLLIDER_BOX, this);
		boxes[4] = App->collision->AddCollider({ 200, 212, 11, 10 }, COLLIDER_BOX, this);
	}
	else if (App->level == 3)
	{

		App->enemies->AddSpawner(ENEMY_GRENADE, 170, 1898, 45, 300, 2, false, &door_bunker1);
		App->enemies->AddSpawner(ENEMY_GRENADE, 42, 1834, 45, 200, 2, false, &door_bunker2);
		App->enemies->AddSpawner(ENEMY_GRENADE, 106, 1577, 45, 400, 2, false, &door_bunker3);
		App->enemies->AddSpawner(ENEMY_GRENADE, 42, 1449, 45, 330, 2, false, &door_bunker4);
		App->enemies->AddSpawner(ENEMY_GRENADE, 106, 1193, 45, 350, 2, false, &door_bunker5);
		App->enemies->AddSpawner(ENEMY_GRENADE, 170, 1257, 45, 280, 2, false, &door_bunker6);


		//Colliders of the bridge
		App->collision->AddCollider({ 20, 942, 78, 77 }, COLLIDER_WALL);
		App->collision->AddCollider({ 159, 942, 80 ,77 }, COLLIDER_WALL);


		//Colliders of the final door wall
		App->collision->AddCollider({ 0, 0, 87, 42 }, COLLIDER_WALL);
		App->collision->AddCollider({ 170, 0, 86, 42 }, COLLIDER_WALL);


		//Colliders of the  walls at the part after the bridge
		App->collision->AddCollider({ 28, 85, 23, 10 }, COLLIDER_WALL);
		App->collision->AddCollider({ 51, 77, 12, 11 }, COLLIDER_WALL);

		App->collision->AddCollider({ 205, 85, 23, 10 }, COLLIDER_WALL);
		App->collision->AddCollider({ 193, 77, 12, 11 }, COLLIDER_WALL);

		App->collision->AddCollider({ 96, 838, 27, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 84, 844, 12, 17 }, COLLIDER_WALL);
		App->collision->AddCollider({ 79,853, 5, 8 }, COLLIDER_WALL);
		App->collision->AddCollider({ 71,858, 8, 8 }, COLLIDER_WALL);

		//Colliders of the "fosses"
		App->collision->AddCollider({ 139, 1441, 73, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 11, 1250, 73, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 172, 1187, 38, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 44, 1123, 38, 5 }, COLLIDER_WALL);

		App->collision->AddCollider({ 139, 1449, 73, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 11, 1258, 73, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 172, 1192, 38, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 44, 1128, 38, 5 }, COLLIDER_WALL);

		//colliders for bunkers( backward 3 rows left)
		App->collision->AddCollider({ 68, 1953, 47, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 73, 1942, 37, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 81, 1938, 22, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 84, 1977, 19, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 74, 1970, 34, 4 }, COLLIDER_WALL);

		App->collision->AddCollider({ 132, 1631, 47, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 137, 1620, 37, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 145, 1616, 22, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 148, 1655, 19, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 138, 1648, 34, 4 }, COLLIDER_WALL);

		App->collision->AddCollider({ 196, 1504, 47, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 201, 1493, 37, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 209, 1489, 22, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 212, 1528, 19, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 202, 1521, 34, 4 }, COLLIDER_WALL);

		//colliders for bunkers( backward 3 rows right)
		App->collision->AddCollider({ 109, 1759, 47, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 112, 1750, 37, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 124, 1745, 22, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 122, 1783, 19, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 117, 1776, 34, 4 }, COLLIDER_WALL);

		App->collision->AddCollider({ 45, 1311, 47, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 48, 1302, 37, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 60, 1297, 22, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 58, 1335, 19, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 53, 1328, 34, 4 }, COLLIDER_WALL);

		App->collision->AddCollider({ 173, 1119, 47, 14 }, COLLIDER_WALL);
		App->collision->AddCollider({ 176, 1110, 37, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 188, 1105, 22, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 186, 1143, 19, 4 }, COLLIDER_WALL);
		App->collision->AddCollider({ 181, 1136, 34, 4 }, COLLIDER_WALL);

		//colliders for bunkers( part of one in the left)
		App->collision->AddCollider({ 21, 1627, 8, 22 }, COLLIDER_WALL);

		//colliders for bunkers( beginning right)
		App->collision->AddCollider({ 236, 1944, 19, 25 }, COLLIDER_WALL);

		//colliders for bunkers( door looking right)
		App->collision->AddCollider({ 186, 1885, 2, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 156, 1894, 9, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 143, 1881	, 39,22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 151, 1875, 23, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 152, 1911, 24, 2 }, COLLIDER_WALL);

		App->collision->AddCollider({ 58, 1821, 2, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 28, 1830, 9, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 12, 1819,39,22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 23, 1811, 23, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 24, 1847, 24, 2 }, COLLIDER_WALL);

		App->collision->AddCollider({ 186, 1244, 2, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 156, 1253, 9, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 143, 1240	,39,22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 151, 1234, 23, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 152, 1270, 24, 2 }, COLLIDER_WALL);

		App->collision->AddCollider({ 122, 1564, 2, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 92, 1573, 9, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 81, 1560	,39,22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 87, 1554, 23, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 88, 1590, 24, 2 }, COLLIDER_WALL);

		App->collision->AddCollider({ 58, 1436, 2, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 28, 1445, 9, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 12, 1434	,39,22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 23, 1426, 23, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 24, 1462, 24, 2 }, COLLIDER_WALL);

		App->collision->AddCollider({ 122, 1180, 2, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 92, 1189, 9, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 81, 1176	,39,22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 87, 1170, 23, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 88, 1206, 24, 2 }, COLLIDER_WALL);

		//colliders for bunkers( door looking left)
		App->collision->AddCollider({ 165, 1691, 2, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 187, 1701, 9, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 169, 1688	,39,22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 177, 1683, 23, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 175, 1718, 24, 2 }, COLLIDER_WALL);

		App->collision->AddCollider({ 37, 1691, 2, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 59, 1701, 9, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 42, 1688	,39,22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 49, 1683, 23, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 47, 1718, 24, 2 }, COLLIDER_WALL);

		App->collision->AddCollider({ 101, 1372, 2, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 123, 1382, 9, 22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 106, 1369	,39,22 }, COLLIDER_WALL);
		App->collision->AddCollider({ 113, 1363, 23, 5 }, COLLIDER_WALL);
		App->collision->AddCollider({ 111, 1399, 24, 2 }, COLLIDER_WALL);

		if (sprite_graphics == nullptr)
			ret = false;

	}
	return ret;
}



update_status ModuleObjects::Update() {
	if (App->level == 3)
	{
		//Animations of the door of the bunkers
		App->render->Blit(sprite_graphics, 170, 1893, &door_bunker1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 42, 1829, &door_bunker2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 106, 1572, &door_bunker3.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 42, 1444, &door_bunker4.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 106, 1188, &door_bunker5.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 170, 1252, &door_bunker6.GetCurrentFrame().rect);

		//Animations of the door of the bunkers but left side
		App->render->Blit(sprite_graphics, 42, 1700, &door_bunker_left1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 170, 1700, &door_bunker_left2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 106, 1380, &door_bunker_left3.GetCurrentFrame().rect);


		//Final door animation
		App->render->Blit(sprite_graphics, 83, 0, &final_door.GetCurrentFrame().rect);

		//Mortars
		if (App->player->position.x < level_dimensions.x / 4)
		{
			App->render->Blit(sprite_graphics, 210, 70, &mortar_left1.GetCurrentFrame().rect);
			App->render->Blit(sprite_graphics, 30, 70, &mortar_right1.GetCurrentFrame().rect);
		}
		else if (App->player->position.x >= level_dimensions.x / 4 && App->player->position.x < ((level_dimensions.x / 4) * 2))
		{
			App->render->Blit(sprite_graphics, 210, 70, &mortar_left2.GetCurrentFrame().rect);
			App->render->Blit(sprite_graphics, 30, 70, &mortar_right2.GetCurrentFrame().rect);
		}
		else if (App->player->position.x >= ((level_dimensions.x / 4) * 2) / 4 && App->player->position.x < ((level_dimensions.x / 4) * 3))
		{
			App->render->Blit(sprite_graphics, 210, 70, &mortar_left3.GetCurrentFrame().rect);
			App->render->Blit(sprite_graphics, 30, 70, &mortar_right3.GetCurrentFrame().rect);
		}
		else if (App->player->position.x >= ((level_dimensions.x  / 4) * 3) / 4 && App->player->position.x < level_dimensions.x)
		{
			App->render->Blit(sprite_graphics, 210, 70, &mortar_left4.GetCurrentFrame().rect);
			App->render->Blit(sprite_graphics, 30, 70, &mortar_right4.GetCurrentFrame().rect);
		}
	}
	else if (App->level == 4)
	{
		App->render->Blit(sprite_graphics, 200, 1690, &box.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 50, 1320, &box2.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 62, 910, &box.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 174, 676, &box.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 200, 366, &box3.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 18, 1471, &tree1.GetCurrentFrame().rect);

		App->render->Blit(sprite_graphics, 130, 1423, &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 145, 1410, &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 159, 1423, &tree2.GetCurrentFrame().rect);

		App->render->Blit(sprite_graphics, 162, 958, &tree1.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 59, 470, &bunker_house.GetCurrentFrame().rect);
		App->render->Blit(sprite_graphics, 16, 1375, &trinxera.GetCurrentFrame().rect);

	}
	else if (App->level == 1)
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

		//To see if the animation of the bunkers doors of the third level work well
		//App->render->Blit(sprite_graphics, 50, -340 + level_dimensions.y, &door_bunker.GetCurrentFrame().rect);

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

		//Final door animation
		App->render->Blit(sprite_graphics, 83, 0,&final_door.GetCurrentFrame().rect);


	
		//Boxes
		for (int i = 0; i < 10; i++) {
			if (boxes[i] != nullptr) {
				App->render->Blit(sprite_graphics, boxes[i]->rect.x, boxes[i]->rect.y, &box.GetCurrentFrame().rect);
			}
		}
		
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
					tree1.speed = 0.03f;
					tree2.speed = 0.03f;			
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
					tree1.speed = 0.02f;
					tree2.speed = 0.02f;
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
		else
		{
			tree1.speed = 0;
			tree2.speed = 0;
		}
	}


	SDL_Rect player_grenade_num = { 42, 496, 10, 13 };
	App->render->Blit(sprite_graphics, SCREEN_WIDTH /3 + 15, SCREEN_HEIGHT-18, &player_grenade_num, 0.0f, false);
	SDL_Rect player_lives_spr = { 22,496,11,16 };
	for (int i = 0; i < (App->player->lives - 1); i++) {
		App->render->Blit(sprite_graphics, 3 + i * 13, SCREEN_HEIGHT - 18, &player_lives_spr, 0.0f, false);
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

void ModuleObjects::OnCollision(Collider* self, Collider* other) {
	for (int i = 0; i < 10; i++) {
		if (boxes[i] == self) {
			App->collision->EraseCollider(self);
			App->scene_game->score = App->scene_game->score +1000;
			boxes[i] = nullptr;
		}
	}
	if (App->player->grenades < 6) App->player->grenades++;
}
