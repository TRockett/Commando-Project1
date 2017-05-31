#include "ModuleSceneCongrats.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneWelcome.h"
#include "ModuleSound.h"
#include "ModuleFonts.h"
#include "ModuleSceneGame.h"

ModuleSceneCongrats::ModuleSceneCongrats()
{
}


ModuleSceneCongrats::~ModuleSceneCongrats()
{
}

bool ModuleSceneCongrats::Init() {
	return true;
}

bool ModuleSceneCongrats::Start() {
	bool ret = true;

	uint score = App->interfac->score;

	for (uint i = 0; i < MAX_SCORES; i++) {
		if (score > App->interfac->max_scores[i]) {
			for (uint j = MAX_SCORES - 1; j > i; j--) {
				App->interfac->max_scores[j] = App->interfac->max_scores[j - 1];
				App->interfac->score_names[j] = App->interfac->score_names[j - 1];
			}
			App->interfac->max_scores[i] = score;
			App->interfac->score_names[i] = "Player.1..";
			break;
		}
	}

	App->interfac->UpdateScores();

	App->interfac->score = 0;

	App->interfac->Enable();
	App->fonts->Enable();
	App->textures->Enable();

	font_yellow = App->fonts->Load("Images/Fuentes_small_yellow.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	font_white = App->fonts->Load("Images/Fuentes_small_grey.png", "0123456789ABCDEF\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1           K;®.,0123456789=      ABCDEFGHIJKLMNOPQRSTUVWXYZ.\1\1   abcdefghijklmnopqrstuvwxyz    |                                ", 5, 0, 1);
	App->player->lives = 3;
	App->player->grenades = 6;
	background_graphics = App->textures->Load("Images/Mapa4.png");
	title_graphics = App->textures->Load("Images/title.png");
	capcom = App->textures->Load("Images/capcom.png");

	App->interfac->AddLabel(font_yellow, "RANKING BEST 7", SCREEN_WIDTH / 2, 95, ALIGNMENT_CENTRE);
	for (uint i = 0; i < MAX_SCORES; i++) {
		char* str = (char*)malloc(4 * sizeof(char));
		if (i == 0)
			sprintf_s(str, 4, "%dST", i + 1);
		else if (i == 1)
			sprintf_s(str, 4, "%dND", i + 1);
		else sprintf_s(str, 4, "%dTH", i + 1);


		App->interfac->AddLabel(font_white, str, 23, 110 + 16 * i);
		App->interfac->AddLabel(font_white, App->interfac->score_texts[i], 65 + 8 * 6, 110 + 16 * i, ALIGNMENT_RIGHT);
		App->interfac->AddLabel(font_white, App->interfac->score_names[i], 120, 110 + 16 * i, ALIGNMENT_LEFT, true);
	}


	if (background_graphics == nullptr)
		ret = false;

	if (App->sound->LoadMusic("Soundtrack/13. Namen eingeben.wav") == nullptr)
		ret = false;

	if (title_graphics == nullptr)
		ret = false;

	if (capcom == nullptr)
		ret = false;
	return ret;
}

update_status ModuleSceneCongrats::PreUpdate() {
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
		App->fade->FadeToBlack(this, App->scene_welcome, 1.0f);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleSceneCongrats::Update() {
	SDL_Rect target = { 20, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	App->render->Blit(background_graphics, 0, 0, &target, 0.0f);
	App->render->Blit(title_graphics, 8, 56, 0 , 0.0f);
	App->render->Blit(capcom, 29, SCREEN_HEIGHT - 36,0 , 0.0f);
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleSceneCongrats::PostUpdate() {
	return update_status::UPDATE_CONTINUE;
}

bool ModuleSceneCongrats::CleanUp() {
	bool ret = true;
	App->sound->StopAll();
	App->fonts->Disable();
	App->textures->Disable();
	App->interfac->Disable();
	
	return ret;
}

void ModuleSceneCongrats::onFadeInEnd() {
	App->sound->PlayMusic();
}