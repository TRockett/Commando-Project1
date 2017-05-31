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
	bool ranking;
	Text_alignment alignment;

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
	int AddLabel(int id, const char* text, int posx, int posy, Text_alignment alignment = ALIGNMENT_LEFT, bool ranking = false);
	Label* getLabel(int id);
	bool CleanUp();
	void UpdateScores();

	uint score;
	uint max_scores[MAX_SCORES];
	char* score_names[MAX_SCORES];
	char* score_texts[MAX_SCORES];
};

