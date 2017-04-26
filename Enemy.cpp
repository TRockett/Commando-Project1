#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "EnemyLeft.h"
#include "ModuleRender.h"
#include "ModuleSceneGame.h"
#include <math.h>

Enemy::Enemy(int x, int y) : position(x, y), initial_position(x, y)
{}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	if (animation != nullptr) {
		current_frame = animation->GetCurrentFrame();
		App->render->Blit(sprites, position.x - current_frame.pivot.x, position.y - current_frame.pivot.y, &(current_frame.rect));
	}

	if (collider != nullptr) {
		//collider->SetPos(position.x, position.y);
		collider->rect = { position.x - current_frame.pivot.x, position.y - current_frame.pivot.y, current_frame.rect.w, current_frame.rect.h };
	}
}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_WALL)
	{
		
	}
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y, EXPLOSION,COLLIDER_ENEMY);
}
int Enemy::Collisionangle(Collider* c1, Collider* c2)
{
	iPoint dimensions = App->scene_game->getLevelDimensions();
	iPoint diference;
	diference.y = (c2->rect.y) - (c1->rect.y);
	diference.x = (c2->rect.x) - (c1->rect.x);

	int angle = 0;
	if (diference.y == 0)
	{
		if (diference.x > 0)
		{
			angle = 90;
		}
		else
			angle = -90;
	}
	else if (diference.x == 0)
	{
		if (diference.x > 0)
		{
			angle = 180;
		}
		else
			angle = -180;

	}
	else 
		angle = asin(diference.y / diference.x)* 180.0 / M_PI;

	return angle;
	
}