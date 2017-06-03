#include "ModuleLevel4.h"
#include "ModuleLevel3.h"
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
#include "ModuleObjects.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL_timer.h"
#include "EnemyVehicles.h"




ModuleLevel4::ModuleLevel4()
{
	intro = true;
	next = this;
}


ModuleLevel4::~ModuleLevel4()
{
}


bool ModuleLevel4::Start() {
	screen_enemies = 0;
	bool ret = true;
	restart = false;
	global = false;
	global_on = true;
	App->level = 4;
	App->current_scene = this;
	intro = false;
	background_graphics = App->textures->Load("Images/Mapa4.png", &level_dimensions);


	spawning = false;
	counter = 0;

	App->render->camera.x = -20 * SCREEN_SIZE;
	App->render->camera.y = (-level_dimensions.y + SCREEN_HEIGHT) * SCREEN_SIZE;


	App->enemies->AddEnemy(MOTOLEVEL3, 0 - 46, 320, 270, 1);
	App->enemies->AddEnemy(MOTOLEVEL3, 0 - 46, 300, 270, 1);

	App->enemies->AddEnemy(ENEMY_TOWER, 210, 618, 0, 1);
	App->enemies->AddEnemy(ENEMY_TOWER, 57, 84, 0, 2);
	App->enemies->AddEnemy(ENEMY_TOWER, 182, 84, 0, 2);
	App->enemies->AddEnemy(ENEMY_TOWER, 100, 18, 0, 2);
	App->enemies->AddEnemy(ENEMY_TOWER, 140, 18, 0, 2);
	App->enemies->AddEnemy(ENEMY_GRENADE, 25, 1365, 0, 6);
	App->enemies->AddEnemy(ENEMY_GRENADE, 50, 1365, 0, 6);

	App->enemies->AddEnemy(MOTOLEVEL3, 0 - 46, 830, 270, 1);
	App->enemies->AddEnemy(MOTOLEVEL3, 0 - 46, 770, 270, 1);
	App->enemies->AddEnemy(MOTOLEVEL3, 0 - 46, 720, 270, 1);

	App->enemies->AddEnemy(LEFT_WEAPON, 0, 1845, 90, 1);
	App->enemies->AddSpawner(LEFT_WEAPON, 0, 1845, 90, 465, 1, 0, nullptr,0, 15);

	App->enemies->AddEnemy(LEFT_WEAPON, SCREEN_WIDTH, 1845, 270, 1);
	App->enemies->AddSpawner(LEFT_WEAPON, SCREEN_WIDTH, 1845, 270, 370, 1, 0 ,nullptr,0 , 15);

	App->enemies->AddEnemy(ENEMY_GRENADE, 0, 1810, 90, 1);
	App->enemies->AddSpawner(ENEMY_GRENADE, 0, 1810, 90, 350, 1, 0, nullptr, 0, 10);

	
	App->enemies->AddSpawner(ENEMY_GRENADE, SCREEN_WIDTH, 1810, 270, 400, 1, 0, nullptr, 0, 10);

	
	App->enemies->AddSpawner(LEFT_WEAPON, 0, 1790, 90, 485, 1, 0, nullptr, 0, 15);

	
	App->enemies->AddSpawner(LEFT_WEAPON, SCREEN_WIDTH, 1790, 270, 450, 1, 0, nullptr, 0, 15);

	App->enemies->AddEnemy(LEFT_WEAPON, 0, 1720, 90, 1);
	App->enemies->AddSpawner(LEFT_WEAPON, 0, 1720, 90, 390, 1, 0, nullptr, 0, 20);

	
	App->enemies->AddSpawner(LEFT_WEAPON, SCREEN_WIDTH, 1720, 270, 450, 1, 0, nullptr, 0, 20);

	App->enemies->AddEnemy(LEFT_WEAPON, 0, 1660, 90, 1);
	App->enemies->AddSpawner(LEFT_WEAPON, 0, 1660, 90, 355, 1, 0, nullptr, 0, 20);

	App->enemies->AddEnemy(ENEMY_BAZOOKA, SCREEN_WIDTH, 1660, 270, 1);
	App->enemies->AddSpawner(ENEMY_BAZOOKA, SCREEN_WIDTH, 1660, 270, 370, 1, 0, nullptr, 0, 20);

	
	App->enemies->AddSpawner(LEFT_WEAPON, 0, 1530, 90, 300, 1, 0, nullptr, 0, 10);

	App->enemies->AddEnemy(LEFT_WEAPON, SCREEN_WIDTH, 1530, 270, 1);
	App->enemies->AddSpawner(LEFT_WEAPON, SCREEN_WIDTH, 1530, 270, 350, 1, 0, nullptr, 0, 15);

	Global = App->enemies->AddSpawner(LEFT_WEAPON, 0, 0, 0, 80, 1, 1);
	Global->active = false;
		
	App->enemies->AddEnemy(ENEMY_GRENADE, 0, 1020, 90, 1);
	App->enemies->AddSpawner(ENEMY_GRENADE, 0, 970, 90, 450, 1, 0, nullptr, 0, 15);

	App->enemies->AddEnemy(ENEMY_GRENADE, SCREEN_WIDTH, 900, 270, 1);
	App->enemies->AddSpawner(ENEMY_GRENADE, SCREEN_WIDTH, 900, 270, 350, 1, 0, nullptr, 0, 15);

	App->enemies->AddEnemy(ENEMY_BAZOOKA, 0, 540, 90, 1);
	App->enemies->AddSpawner(ENEMY_BAZOOKA, 0, 540, 90, 350, 1, 0, nullptr, 0, 10);

	App->enemies->AddEnemy(ENEMY_BAZOOKA, SCREEN_WIDTH, 500, 270, 1);
	App->enemies->AddSpawner(ENEMY_BAZOOKA, SCREEN_WIDTH, 500, 270, 450, 1, 0, nullptr, 0, 10);


	font_red = App->fonts->Load("Images/Fuentes_small_red.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;�.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	font_white = App->fonts->Load("Images/Fuentes_small_grey.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;�.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);

	App->interfac->AddLabel(font_red, "1UP", 15, 0);
	App->interfac->AddLabel(font_red, "TOP SCORE", SCREEN_WIDTH / 2 - 30, 0);
	App->interfac->AddLabel(font_white, App->interfac->score_texts[0], SCREEN_WIDTH / 2 - 15, 8);

	grenade_label = App->interfac->getLabel(App->interfac->AddLabel(font_white, "", SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT - 15));
	score_label = App->interfac->getLabel(App->interfac->AddLabel(font_white, "", SCREEN_WIDTH / 2 - 103, 8));

	//Enabling modules
	App->player->Enable();
	App->collision->Enable();
	App->objects->Enable();
	App->particles->Enable();
	App->enemies->Enable();
	App->fonts->Enable();
	App->interfac->Enable();

	newstart = App->sound->LoadMusic("Soundtrack/4. Neustart.wav");
	music = App->sound->LoadMusic("Soundtrack/3.Hintergrundmusik 1.wav");
	if (music == nullptr || newstart == nullptr)
		ret = false;
	if (background_graphics == nullptr)
		ret = false;

	App->sound->StopMusic();
	App->sound->PlayMusic(newstart, 0);
	App->sound->ExecuteOnMusicEnd(PlayMainMusic);

	return ret;
}

update_status ModuleLevel4::PreUpdate() {

	if (restart) {
		App->fade->FadeToBlack(this, next, 0.0f);
		screen_enemies = 0;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleLevel4::Update() {
	bool ret = true;


	ret = App->render->Blit(background_graphics, 0, 0, nullptr);

	sprintf_s(score_text, 10, "%7d", App->interfac->score);

	grenade_str = "= ";
	grenade_str.append(std::to_string(App->player->grenades));

	grenade_label->setString(grenade_str.c_str());
	score_label->setString(score_text);

	if (App->player->position.y <= 1280)
	{
		global = true;
	}
	if (global == true && global_on == true)
	{

		global_on = false;
		Global->active = true;
	}

	if (App->player->position.y <= SCREEN_HEIGHT - 100)
	{
		if (spawning == false)
		{
			Global->active = false;
			timer = SDL_GetTicks();
			spawning = true;
			App->objects->final_door.speed = 0.05f;
		}
		else if (timer + 1500 < SDL_GetTicks() && counter < 5)
		{
			App->enemies->AddEnemy(ENEMY_GRENADE, ((rand() % 130) + (SCREEN_WIDTH - 30)) / 2, 81, 0, 2);
			timer = SDL_GetTicks();
			counter++;
		}
		else if (timer + 2000 < SDL_GetTicks() && App->player->final_anim == 0)
		{
			App->player->final_anim = 1;
			App->enemies->Disable();
		}
	}

	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
}

update_status ModuleLevel4::PostUpdate() {
	if (App->player->final_anim == 9)
	{
		App->fade->FadeToBlack(this, App->scene_congrats, 3.0f);

	}
	return UPDATE_CONTINUE;
}

bool ModuleLevel4::CleanUp() {
	bool ret = true;
	restart = false;
	App->sound->StopAll();
	App->player->Disable();
	App->collision->Disable();
	App->enemies->Disable();
	App->objects->Disable();
	App->particles->Disable();
	App->fonts->Disable();
	App->interfac->Disable();
	ret = App->textures->Unload(background_graphics);

	return ret;
}

void ModuleLevel4::onFadeInEnd() {
	restart = false;
}



