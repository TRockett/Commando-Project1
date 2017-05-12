#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "EnemyLeft.h"
#include "ModuleRender.h"
#include "ModuleSceneGame.h"
#include <math.h>

Enemy::Enemy(int x, int y, int angle, int sub_type) : position(x, y), initial_position(x, y), initial_angle(angle),sub_type(sub_type)
{}

Enemy::~Enemy()
{
}

Collider* Enemy::GetCollider() const
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
	if (collider->type == COLLIDER_WALL || collider->type == COLLIDER_WATER)
	{
		collision = true;

	}
	if (collider->type == COLLIDER_PLAYER_SHOT)
	{
		dying = true;
	}
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y, EXPLOSION,COLLIDER_ENEMY);
}
int Enemy::Collisionangle(int angle)
{
	angle += 180;
	if (angle > 360)
	{
		angle -= 360;
	}
	return angle;
	
}

Animation* Enemy::GetAnimationForDirection(int dir) {
	Animation* animation = nullptr;
	if (dir < 22 || dir > 338)
	{
		shooting_position = { 3,14 };
		animation = &e1_forward;
	}

	else if (dir >= 22 && dir < 67)
	{
		shooting_position = { 0,6 };
		animation = &e1_up_left;
	}
	else if (dir >= 67 && dir < 112)
	{
		shooting_position = { 15,12 };
		animation = &e1_right;
	}
	else if (dir >= 112 && dir < 157)
	{
		shooting_position = { 9,15 };
		animation = &e1_down_left;
	}

	else if (dir >= 157 && dir < 202)
	{
		shooting_position = { 11,4 };
		animation = &e1_backward;
	}

	else if (dir >= 202 && dir < 247)
	{
		shooting_position = { 7,15 };
		animation = &e1_down_right;
	}

	else if (dir >= 247 && dir < 292)
	{
		shooting_position = { 2,12 };
		animation = &e1_left;
	}

	else if (dir >= 292 && dir < 338)
	{
		shooting_position = { 15,6 };
		animation = &e1_up_right;
	}

	return animation;
}


