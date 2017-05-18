#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleSceneWelcome;
class ModuleSceneGame;
class ModuleSceneCongrats;
class ModuleSound;
class ModuleCollision;
class ModuleParticles;
class ModuleEnemies;
class ModuleFonts;
class Module;
class ModuleObjects;
class ModuleLevel3;
class ModuleLevel4;
class ModuleLevelTransition;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleSound* sound;
	ModuleSceneWelcome* scene_welcome;
	ModuleSceneCongrats* scene_congrats;
	ModuleSceneGame* scene_game;
	ModuleCollision* collision;
	ModuleParticles* particles;
	ModuleEnemies* enemies;
	ModuleFonts* fonts;
	ModuleObjects* objects;
	ModuleLevel3 *level_3;
	Module* current_scene;
	ModuleLevel4 * level_4;
	ModuleLevelTransition* transition;


public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	int level = 1;

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__