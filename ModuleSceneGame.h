#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneGame :
	public Module
{
private:
	int level;
public:
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	ModuleSceneGame();
	~ModuleSceneGame();
};

