#pragma once
#include "Module.h"
#include "Animation.h"

#define MAX_LABELS 64
#define MAX_SCORES 7

enum Text_alignment {
	ALIGNMENT_LEFT,
	ALIGNMENT_RIGHT,
	ALIGNMENT_CENTRE
};

struct Label {
	int font_id;
	const char* string;
	iPoint pos;
	Text_alignment alignment;
	uint tickrate;
	uint born;
	int life;
	uint start_time;
	bool visible = true;

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
	int AddLabel(int id, const char* text, int posx, int posy, Text_alignment alignment = ALIGNMENT_LEFT, int life = -1);
	bool RemoveLabel(Label* label);
	bool RemoveLabel(int label_id);
	Label* getLabel(int id);
	bool CleanUp();
	void UpdateScores();

	uint score;
	uint max_scores[MAX_SCORES];
	char* score_names[MAX_SCORES];
	char* score_texts[MAX_SCORES];
};

