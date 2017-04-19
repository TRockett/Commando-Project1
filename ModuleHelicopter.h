#pragma once
#include "Module.h"

struct SDL_Texture;

class ModuleHelicopter :
	public Module
{

public:
	SDL_Texture* sprites = nullptr;
	Animation* current_animation = nullptr;
	Animation helix1;
	ModuleHelicopter();
	virtual ~ModuleHelicopter();
};

