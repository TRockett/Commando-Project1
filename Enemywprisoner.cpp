#include "Enemywprisoner.h"
#include "ModuleCollision.h"
#include "Application.h"


Enemywprisoner::Enemywprisoner(int x, int y) : Enemy (x, y)
{
	walking.PushBack({});




	//collider = App->collision->AddCollider({ 0, 0, 15, 23 }, COLLIDER_ENEMY, App->enemies);


	movement.PushBack({ 3.0f, 3.0f }, 100, animation);

	animation = &walking;

	movement.loop = false;
};


Enemywprisoner::~Enemywprisoner()
{
};

//void Enemywprisoner::Move() {
//	position = initial_position + movement.GetCurrentPosition();
//	if (movement.Finished())
//	{
//		movement.Clear();
//		movement.Reset();
//		int angle = (rand() % 8) * 45 /* (M_PI / 180.0f)*/;
//		animation = GetAnimationForDirection(angle);
//		movement.PushBack({ sinf((float)angle), cosf((float)angle) }, 100);
//	}
//}