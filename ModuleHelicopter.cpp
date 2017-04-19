//#include "ModuleHelicopter.h"
//#include "Animation.h"
//#include "Path.h"
//#include "Application.h"
//#include "ModuleTextures.h"
//#include "ModuleRender.h"
//
//
//ModuleHelicopter::ModuleHelicopter()
//{
//	helix1.PushBack({785, 419, 96, 33 });
//	helix1.PushBack({ 875, 459, 96, 33 });
//	helix1.PushBack({ 800, 553, 79, 21 });
//	helix1.PushBack({ 857, 503, 42, 45 });
//	helix1.PushBack({ 865, 588, 26, 27 });
//	helix1.PushBack({ 877, 393, 79, 21 });
//
//	helix1.loop = true;
//	helix1.speed = 0.25f;
//
//
//	helix2.PushBack({});
//
//}
//
//
//ModuleHelicopter::~ModuleHelicopter()
//{
//}
//
//bool ModuleHelicopter::Start() {
//	bool ret = true;
//
//	helicopter_1 = App->textures->Load("Images/sprites.png");
//	helicopter_2 = App->textures->Load("Images/sprites.png");
//	helicopter_3 = App->textures->Load("Images/sprites.png");
//
//	if (helicopter_1 == nullptr)
//		ret = false;
//	if (helicopter_2 == nullptr)
//		ret = false;
//	if (helicopter_3 == nullptr)
//		ret = false;
//
//	return ret;
//}
//
//update_status ModuleHelicopter::Update() 
//{
//	
//	App->render->Blit(helicopter_1, 710, 440, &helicopter1.GetCurrentFrame().rect);
//
//
//}