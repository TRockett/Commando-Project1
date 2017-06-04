#include "ModuleInterface.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleFonts.h"
#include <stdlib.h>
#include <stdio.h>
#include "SDL\include\SDL_timer.h"


ModuleInterface::ModuleInterface()
{
}


ModuleInterface::~ModuleInterface()
{
}


bool ModuleInterface::Init() {

	graphics = nullptr;
	score = 0;

	max_scores[0] = 50000;
	max_scores[1] = 30000;
	max_scores[2] = 20000;
	max_scores[3] = 19420;
	max_scores[4] = 12000;
	max_scores[5] = 10000;
	max_scores[6] = 8000;

	/*for (uint i = 0; i < MAX_SCORES; i++)
		score_names[i] = (char*)malloc(10 * sizeof(char));*/

	score_names[0] = "NINALB.SUX";
	score_names[1] = "POL.2.....";
	score_names[2] = "MARC.GG...";
	score_names[3] = "CAPCOM....";
	score_names[4] = "EXED.EXES.";
	score_names[5] = "PATIUS....";
	score_names[6] = "POL.1.....";


	for (uint i = 0; i < MAX_SCORES; i++) {
		score_texts[i] = (char*)malloc(7 * sizeof(char));
		sprintf_s(score_texts[i], 7, "%d", max_scores[i]);
	}

	return true;
}

bool ModuleInterface::Start() {
	bool ret = true;

	graphics = App->textures->Load("Images/sprites.png");

	if (graphics == nullptr)
		ret = false;
	
	return ret;
}

update_status ModuleInterface::PostUpdate() {

	for (uint i = 0; i < MAX_LABELS; i++) {
		Label* label = labels[i];
		if (label == nullptr)
			continue;

		if (label->life < 0) {
			App->fonts->BlitText(label);
			continue;
		}
		
		uint ticks = SDL_GetTicks();
		if (ticks > label->start_time + label->tickrate) {
			label->visible = !label->visible;
			label->start_time = ticks;
		}

		if (ticks > label->born + label->life) {
			RemoveLabel(label);
			continue;
		}

		if (label->visible)
			App->fonts->BlitText(label);
	}

	return UPDATE_CONTINUE;
}

bool ModuleInterface::CleanUp() {
	bool ret = true;

	ret = App->textures->Unload(graphics);
	for (uint i = 0; i < MAX_LABELS; i++) {
		if (labels[i] != nullptr) {
			//delete[] labels[i]->string;
			delete labels[i];
			labels[i] = nullptr;
		}
	}

	return ret;
}

int ModuleInterface::AddLabel(int id, const char* text, int posx, int posy, Text_alignment alignment, int life) {
	bool ret = false;

	for (int i = 0; i < MAX_LABELS; i++) {
		if (labels[i] == nullptr) {
			labels[i] = new Label();
			labels[i]->font_id = id;
			labels[i]->pos = { posx, posy };
			labels[i]->string = text;
			labels[i]->tickrate = 333;
			labels[i]->alignment = alignment;
			labels[i]->born = labels[i]->start_time = SDL_GetTicks();
			labels[i]->life = life;
			return i;
		}
	}
}

Label* ModuleInterface::getLabel(int id) {
	return labels[id];
}

void ModuleInterface::UpdateScores() {
	for (uint i = 0; i < MAX_SCORES; i++) {
		score_texts[i] = (char*)malloc(7 * sizeof(char));
		sprintf_s(score_texts[i], 7, "%d", App->interfac->max_scores[i]);
	}
}

bool ModuleInterface::RemoveLabel(Label* label) {
	if (label == nullptr)
		return false;

	for (uint i = 0; i < MAX_LABELS; i++) {
		if (label == labels[i]) {
			delete labels[i];
			labels[i] = nullptr;
			return true;
		}
	}
}

bool ModuleInterface::RemoveLabel(int label_id) {
	if (labels[label_id] == nullptr)
		return false;

	delete labels[label_id];
	labels[label_id] = nullptr;
	return true;
}