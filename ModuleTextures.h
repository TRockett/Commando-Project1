#ifndef __ModuleTextures_H__
#define __ModuleTextures_H__

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_TEXTURES 50

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path, p2Point<int>* dim = nullptr);
	bool Unload(SDL_Texture * texture);

public:
	SDL_Texture* textures[MAX_TEXTURES];
};

#endif // __ModuleTextures_H__