#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation* animation = nullptr;
	Collider* collider = nullptr;
	AnimationFrame current_frame;
	iPoint initial_position;

public:
	iPoint position;
	iPoint prev_position;
	int initial_angle;
	int sub_type;
	bool dead = false;

public:
	Enemy(int x, int y, int angle, int sub_type);
	virtual ~Enemy();

	Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
	virtual int Enemy::Collisionangle(Collider* collider, Collider* c2);
};

#endif // __ENEMY_H__