#include "ModuleInterface.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleFonts.h"


ModuleInterface::ModuleInterface()
{
}


ModuleInterface::~ModuleInterface()
{
}


bool ModuleInterface::Init() {

	graphics = nullptr;

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
		if (labels[i] == nullptr)
			continue;

		App->fonts->BlitText(labels[i]);
	}

	return UPDATE_CONTINUE;
}

bool ModuleInterface::CleanUp() {
	bool ret = true;

	ret = App->textures->Unload(graphics);
	for (uint i = 0; i < MAX_LABELS; i++) {
		if (labels[i] != nullptr) {
			delete labels[i];
			labels[i] = nullptr;
		}

	}

	return ret;
}

int ModuleInterface::AddLabel(int id, const char* text, int posx, int posy) {
	bool ret = false;

	for (int i = 0; i < MAX_LABELS; i++) {
		if (labels[i] == nullptr) {
			labels[i] = new Label();
			labels[i]->font_id = id;
			labels[i]->pos = { posx, posy };
			labels[i]->string = text;
			return i;
		}
	}
}

Label* ModuleInterface::getLabel(int id) {
	return labels[id];
}