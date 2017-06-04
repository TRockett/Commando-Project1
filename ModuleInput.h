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

struct Button {
	KEY_STATE state = KEY_IDLE;

	void setState(bool input) {
		switch (state) {
		case KEY_IDLE:
			state = input ? KEY_DOWN : state;
			break;
		case KEY_DOWN:
			state = input ? KEY_REPEAT : state;
			break;
		case KEY_REPEAT:
			state = input ? state : KEY_UP;
			break;
		case KEY_UP:
			state = input ? KEY_DOWN : KEY_IDLE;
			break;
		}
	}
};

struct GamePad {
	p2Point<float> left_joystick;
	p2Point<float> right_joystick;
	Button back;
	Button start;
	Button left_bumper;
	Button left_trigger;
	Button right_trigger;

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