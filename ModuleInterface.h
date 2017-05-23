#pragma once
#include "Module.h"
#include "Animation.h"
#define MAX_LABELS 64

struct Label {
	int font_id;
	const char* string;
	iPoint pos;

	void setString(const char* str) {
		string = str;
	}
};

struct SDL_Texture;

class ModuleInterface :
	public Module
{
private:
	SDL_Texture* graphics;
	Animation lifes;
	Label* labels[MAX_LABELS];

public:
	ModuleInterface();
	virtual ~ModuleInterface();
	bool Init();
	bool Start();
	update_status PostUpdate();
	int AddLabel(int id, const char* text, int posx, int posy);
	Label* getLabel(int id);
	bool CleanUp();
};

