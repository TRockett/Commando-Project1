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
#include "ModuleObjects.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleLevel3.h"


ModuleSceneGame::ModuleSceneGame()
{
	intro = true;
	next = this;
	
}


ModuleSceneGame::~ModuleSceneGame()
{
}


bool ModuleSceneGame::Start() {
	bool ret = true;
	restart = false;
	App->level = 1;
	App->current_scene = this;

	background_graphics = App->textures->Load("Images/Mapa1.png", &level_dimensions);
	App->render->camera.x = -20 * SCREEN_SIZE;
	App->render->camera.y = (-level_dimensions.y + SCREEN_HEIGHT) * SCREEN_SIZE;

	if (App->level == 1) 
	{
		App->enemies->AddEnemy(MOTO_TYPE, SCREEN_WIDTH, 802, 270, 1);

		App->enemies->AddEnemy(LEFT_WEAPON, 230, 1480, 0, 2);

		App->enemies->AddEnemy(LEFT_WEAPON, 20, 1210, 0, 2);

		App->enemies->AddSpawner(ENEMY_GRENADE, 0, 0, 180, 0, 60, true);
	}

	font_red = App->fonts->Load("Images/Fuentes_small_red.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;�.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	font_white = App->fonts->Load("Images/Fuentes_small_grey.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;�.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);

	App->interfac->AddLabel(font_red, "1up", 15, 0);
	App->interfac->AddLabel(font_red, "top score", SCREEN_WIDTH / 2 - 30, 0);
	App->interfac->AddLabel(font_white, "50000", SCREEN_WIDTH / 2 - 15, 8);
	grenade_label = App->interfac->getLabel(App->interfac->AddLabel(font_white, "", SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT - 15));
	score_label = App->interfac->getLabel(App->interfac->AddLabel(font_white, "", SCREEN_WIDTH / 2 - 103, 8));

	//Enabling modules
	App->collision->Enable();
	App->objects->Enable();
	App->particles->Enable();
	App->fonts->Enable();
	App->interfac->Enable();

	if (background_graphics == nullptr)
		ret = false;

	intro_music = App->sound->LoadMusic("Soundtrack/2.Start-Demo.ogg");
	newstart = App->sound->LoadMusic("Soundtrack/4. Neustart.ogg");
	music = App->sound->LoadMusic("Soundtrack/3.Hintergrundmusik 1.ogg");
	if (music == nullptr || intro_music == nullptr || newstart == nullptr)
		ret = false;

	App->sound->StopMusic();
	if (intro)
		App->sound->PlayMusic(intro_music, 0);
	else {
		App->sound->PlayMusic(newstart, 0);
		App->sound->ExecuteOnMusicEnd(PlayMainMusic);
	}
	
	return ret;
}

update_status ModuleSceneGame::PreUpdate() {

	if (App->input->keyboard[SDL_SCANCODE_3] == KEY_DOWN)
		App->fade->FadeToBlack(this, App->level_3, 3.0f);

	else if (restart) {
		App->fade->FadeToBlack(this, next, 0.0f);
		screen_enemies = 0;
	}
	return UPDATE_CONTINUE;
}

update_status ModuleSceneGame::Update() {
	bool ret = true;
	ret = App->render->Blit(background_graphics, 0, 0, nullptr);
	
	if (App->objects->droping == true)
	{
		App->player->Enable();
		App->enemies->Enable();
		timer = SDL_GetTicks();
	}
	else if(intro == false)
	{
		App->player->Enable();
		App->enemies->Enable();

		App->sound->StopMusic();
		App->sound->PlayMusic(music);
	}
	sprintf_s(score_text, 10, "%7d", App->interfac->score);

	grenade_str = "= ";
	grenade_str.append(std::to_string(App->player->grenades));

	grenade_label->setString(grenade_str.c_str());
	score_label->setString(score_text);

	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
}

update_status ModuleSceneGame::PostUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleSceneGame::CleanUp() {
	App->level = 3;
	
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

void ModuleSceneGame::onFadeInEnd() {
	restart = false;
}