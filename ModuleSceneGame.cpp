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
	level = 1;
	std::string str = "Images/Mapa";
	str.append(std::to_string(level));
	str.append(".png");
	background_graphics = App->textures->Load(str.c_str(), &level_dimensions);
	App->render->camera.x = -20 * SCREEN_SIZE;
	App->render->camera.y = (-level_dimensions.y + SCREEN_HEIGHT) * SCREEN_SIZE;

	App->enemies->AddEnemy(LEFT_WEAPON, 150, 1500);
	App->enemies->AddEnemy(MOTO_TYPE, SCREEN_WIDTH, 802);

	App->enemies->AddEnemy(JUMPING_ENEMY, 230, 1480);

	App->enemies->AddEnemy(JUMPING_ENEMY, 20, 1210);
	
	font = App->fonts->Load("Images/Fuentes_small_red.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 2);
	
	//Enabling modules
	
	App->collision->Enable();
	App->objects->Enable();
	App->particles->Enable();


	if (background_graphics == nullptr)
		ret = false;

	intro_music = App->sound->LoadSound("Soundtrack/2.Start-Demo.wav");
	/*newstart = App->sound->LoadSound("Soundtrack/4. Neustart.wav");*/

	if (intro)
		App->sound->PlaySound(intro_music, 0);

	else {
		App->sound->PlaySound(newstart, 0);
	}
	
	

	//else {
	//	App->sound->PlaySound(newstart, 0);
	//}
	//


	if (App->sound->LoadMusic("Soundtrack/3.Hintergrundmusik 1.wav") == nullptr)
		ret = false;
	
	return ret;
}

update_status ModuleSceneGame::PreUpdate() {
	if (restart) {
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
		if (screen_enemies < 4)
		{
			if (SDL_GetTicks()  >= timer + 200)
			{
				App->enemies->AddEnemy(LEFT_WEAPON, rand() % (SCREEN_WIDTH), (App->player->position.y - (SCREEN_HEIGHT/2) - 20));
				timer = timer + 1000;
				screen_enemies++;
			}
		}

		if (!App->sound->isPlaying()) {
			App->sound->PlayMusic();
		}

	}
	sprintf_s(score_text, 10, "%7d", score);
	return ret ? update_status::UPDATE_CONTINUE : update_status::UPDATE_ERROR;
}

update_status ModuleSceneGame::PostUpdate() {
	App->fonts->BlitText(15, 0, font, "1up");
	App->fonts->BlitText(SCREEN_WIDTH / 2 -30, 0, font, "top score");
	std::string grenade_str = "= ";
	grenade_str.append(std::to_string(App->player->grenades));
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT - 15, font, grenade_str.c_str());
	App->fonts->BlitText(SCREEN_WIDTH / 2 -103, 8, font, score_text);
	App->fonts->BlitText(SCREEN_WIDTH / 2 -15, 8, font,"50000");
	
	return UPDATE_CONTINUE;
}

bool ModuleSceneGame::CleanUp() {
	bool ret = true;
	restart = false;
	App->sound->StopAll();
	App->player->Disable();
	App->collision->Disable();
	App->enemies->Disable();
	App->objects->Disable();
	App->particles->Disable();

	//App->fonts->UnLoad(font);
	ret = App->textures->Unload(background_graphics);

	return ret;
}

void ModuleSceneGame::onFadeInEnd() {
	restart = false;
}