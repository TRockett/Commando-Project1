#ifndef __ModuleLevel4_H__
#define __ModuleLevel4_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleSceneGame.h"
#include "Module.h"
#include "ModuleEnemies.h"
struct SDL_Texture;
struct Mix_Chunk;
class _Mix_Music;
typedef _Mix_Music Mix_Music;

class ModuleLevel4 :
	public ModuleSceneGame
{
public:
	ModuleLevel4();
	virtual ~ModuleLevel4();


	bool spawning;
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void onFadeInEnd();

private:
	Mix_Music* motivationsong;

	int timer1 = 0;

	int counter;
	EnemySpawner* Global;
	bool global;
	bool global_on;
	};

#endif


