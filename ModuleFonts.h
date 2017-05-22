#ifndef __ModuleFonts_H__
#define __ModuleFonts_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_FONTS 60
#define MAX_FONT_CHARS 256
#define MAX_DRAW_PETITIONS 128

struct SDL_Texture;

struct Font
{
	char table[MAX_FONT_CHARS];
	SDL_Texture* graphic = nullptr;
	uint rows, len, char_w, char_h, row_chars;
	uint spacing, margin;
	const char* path;
};

struct DrawPetition {
	int fontID,
		x, y;
	const char* text;
};

class ModuleFonts : public Module
{
public:

	ModuleFonts();
	~ModuleFonts();

	// Load Font
	int Load(const char* texture_path, const char* characters, uint rows = 1, uint margin = 0, uint spacing = 0);
	void UnLoad(int font_id);
	void DrawInterface(int x, int y, int bmp_font_id, const char* text);

	// Create a surface from text
	void BlitText(int x, int y, int bmp_font_id, const char* text) const;
	update_status Update();

private:
	DrawPetition* petitions[MAX_DRAW_PETITIONS];
	Font	 fonts[MAX_FONTS];
};


#endif // __ModuleFonts_H__