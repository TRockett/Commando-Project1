#include "ModuleHelicopter.h"
#include "Animation.h"
#include "Path.h"



ModuleHelicopter::ModuleHelicopter()
{
	helix1.PushBack({785, 419, 96, 33 });
	helix1.PushBack({ 875, 459, 96, 33 });
	helix1.PushBack({ 800, 553, 79, 21 });
	helix1.PushBack({ 857, 503, 42, 45 });
	helix1.PushBack({ 865, 588, 26, 27 });
	helix1.PushBack({ 877, 393, 79, 21 });

	helix1.loop = true;
	helix1.speed = 0.25f;

}


ModuleHelicopter::~ModuleHelicopter()
{
}
