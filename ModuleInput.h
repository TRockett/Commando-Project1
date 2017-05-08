#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GamePad {
	p2Point<float> left_axis;
	p2Point<float> right_axis;
	bool left_trigger;
	bool right_trigger;
	bool left_bumper;
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	SDL_GameController* Controller = nullptr;
	GamePad controller_1;
	bool controller_connected = false;
	KEY_STATE keyboard[MAX_KEYS];
};

#endif // __ModuleInput_H__