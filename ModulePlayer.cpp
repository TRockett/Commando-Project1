#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneGame.h"
//#include "ModuleParticles.h"
#include <math.h>
#include "ModuleSound.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"


ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	// walk forward animation (arcade sprite sheet)
	
	forward.PushBack({0, 0, 13, 23});
	forward.PushBack({14, 0, 13, 22});
	forward.PushBack({ 0, 0, 13, 23 });
	forward.PushBack({28, 0, 13, 22});
	forward.loop = true;
	forward.speed = 0.15f;

	//walk diagonal down-left

	down_left.PushBack({105,24,15,22});
	down_left.PushBack({120,24,15,22});
	down_left.PushBack({105,24,15,22});
	down_left.PushBack({137,24,15,22});
	down_left.speed = 0.15f;

	//walk diagonal down-right

	down_right.PushBack({88,23,15,22});
	down_right.PushBack({56,23,15,22});
	down_right.PushBack({88,23,15,22});
	down_right.PushBack({73,23,15,22});
	down_right.speed = 0.15f;

	//walk diagonal up-right

	up_right.PushBack({0,47,15,22});
	up_right.PushBack({ 38,47,18,21 }, { 2,0 });
	up_right.PushBack({0,47,15,22 });
	up_right.PushBack({16,47,21,21}, { 7,0 });
	up_right.speed = 0.15f;

	//walk diagonal down-left

	up_left.PushBack({97,47,15,22});
	up_left.PushBack({56,47,18,21});
	up_left.PushBack({ 97,47,15,22 });
	up_left.PushBack({75,47,21,21});
	up_left.speed = 0.15f;

	//walk right animation

	
	right.PushBack({ 42,0,19,22 });
	right.PushBack({ 62,0,25,21 }, { 4,0 });
	right.PushBack({ 42,0,19,22 });
	right.PushBack({ 88,0,22,21 }, { 2,0 });
	right.PushBack({ 88,0,22,21 });
	right.loop = true;
	right.speed = 0.15f;
	

	//walk left annimation

	
	left.PushBack({ 160,0,19,22 });
	left.PushBack({ 134,0,25,21 });
	left.PushBack({ 160,0,19,22 });
	left.PushBack({ 111,0,19,22 });
	left.loop = true;
	left.speed = 0.15f;
	
	//walk backward animation

	backward.PushBack({ 28,24,13,22 });
	backward.PushBack({ 0,24,13,22 });
	backward.PushBack({ 28,24,13,22 });
	backward.PushBack({ 13,24,13,22 });
	backward.loop = true;
	backward.speed = 0.15f;
	
	speed = 1;
	shooting = false;

	//death animation
	death.PushBack({170,104, 27, 23});
	death.PushBack({202, 105, 25, 22});
	death.PushBack({235, 104, 15,22});
	death.loop = false;
	death.speed = 0.15f;


	//drown animation
	drown.PushBack({ 270, 40, 17, 23 });
	drown.PushBack({ 296, 40, 25, 14 });
	drown.PushBack({ 334, 40, 15, 12 });
	drown.PushBack({ 357, 40, 14, 12 });
	drown.PushBack({ 377, 40, 15, 13 });
	drown.loop = false;
	drown.speed = 0.10f;

	//throw grenade animation
	throw_grenade.PushBack({ 87,70,17,22 });
	throw_grenade.PushBack({ 109,71,23,21 });
	throw_grenade.PushBack({ 136,68,20,24 });
	throw_grenade.loop = true;
	throw_grenade.speed = 2.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	position.x = SCREEN_WIDTH / 2;
	position.y = App->scene_game->getLevelDimensions().y + 150;
	shooting_angle = 0;
	shooting_position = { 9,1 };
	player_min_y = (int)position.y;
	prev_position = position;
	state = IDLE;
	fire = App->particles->fire_up;
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 13, 23 }, COLLIDER_PLAYER, this);
	LOG("Loading player textures");
	graphics = App->textures->Load("Images/sprites.png"); 

	current_animation= &forward;

	shoot = App->sound->LoadSound("SoundFX/Commando (shoot)_03.wav");
	grenade_explosion = App->sound->LoadSound("SoundFX/Commando (grenade)_02.wav");

	return true;
}

bool ModulePlayer::CleanUp() {
	LOG("Unloading player");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (state != DEAD && !App->scene_game->restart)
	{
		prev_position = position;
		state = IDLE;
		current_animation->speed = 0.15f;
		shooting = false;
		grenade1 = false;

		checkInput();
		processInput();


		if (shooting)
		{
			App->sound->PlaySound(shoot, 0);
			Particle bullet = App->particles->bullet;

			bullet.speed = { (int)(PLAYER_BULLET_SPEED * sinf(shooting_angle * M_PI / 180)), (int)(-PLAYER_BULLET_SPEED * cosf(shooting_angle * M_PI / 180))};
			App->particles->AddParticle(fire, (int)position.x + shooting_position.x + 5 * sinf(shooting_angle * M_PI / 180), (int)position.y + shooting_position.y + 5 * cosf(shooting_angle * M_PI / 180), EXPLOSION, COLLIDER_NONE);
			App->particles->AddParticle(bullet, position.x + shooting_position.x, position.y + shooting_position.y, BULLET, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(bullet, position.x + shooting_position.x, position.y + shooting_position.y, BULLET, COLLIDER_PLAYER_SHOT, nullptr, 50);
		}

		if (grenade_on == false)
		{
			if (grenade1)
			{
				Particle grenade;
				grenade_on = true;
				bthrowing = true;
				grenade = App->particles->grenade;
				grenade.speed = { 0, -1 };
				App->particles->AddParticle(grenade, position.x, position.y, GRENADE_PLAYER, COLLIDER_NONE, grenade_explosion);
			}
			
		}
		else if  (bthrowing == true)
		{
			current_animation = &throw_grenade;
			if (current_animation->Finished() == true)
			{
				bthrowing = false;
				current_animation->Reset();
				state = MOVING_RIGHT;
			}
		}
	}
	else if (current_animation->Finished() && !App->scene_game->restart) {
		App->scene_game->restart = true;
		state = IDLE;
	}


	// Draw everything --------------------------------------
	AnimationFrame frame = current_animation->GetCurrentFrame();


	if (position.x - frame.pivot.x < 20)
		position.x = frame.pivot.x + 20;
	else if (position.x - frame.pivot.x + frame.rect.w > SCREEN_WIDTH + 20)
		position.x = SCREEN_WIDTH + 20 - frame.rect.w + frame.pivot.x;
	if (position.y - frame.pivot.y < 0)
		position.y = frame.pivot.y;
	else if (position.y - frame.pivot.y + frame.rect.h > SCREEN_HEIGHT + (-App->render->camera.y / SCREEN_SIZE))
		position.y = SCREEN_HEIGHT + (-App->render->camera.y / SCREEN_SIZE) - frame.rect.h + frame.pivot.y;

	collider->rect = { (int)position.x - frame.pivot.x, (int)position.y - frame.pivot.y, frame.rect.w, frame.rect.h };

	int margin = 150; //Must be equal to the player's initial position
	player_min_y = MIN(player_min_y, (int)position.y);
	
	if (App->render->camera.y < 0)
		App->render->camera.y = (-player_min_y + margin) * SCREEN_SIZE;
	
	LOG("Player position.y:: %f", position.y);
	LOG("Camera position.y:: %d", App->render->camera.y);

	App->render->Blit(graphics, ((int)position.x - frame.pivot.x), ((int)position.y - frame.pivot.y), &frame.rect);

	return UPDATE_CONTINUE;
}

void ModulePlayer::checkInput() {

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{

		state = MOVING_RIGHT | state;
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		state = MOVING_LEFT | state;
	}

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		state = MOVING_UP | state;
	}
	
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		state = MOVING_DOWN | state;
	}

	if (App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_DOWN)
	{
		shooting = true;
	}
	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN)
	{
		grenade1 = true;
	
	}

	if (App->input->keyboard[SDL_SCANCODE_LSHIFT] == KEY_STATE::KEY_REPEAT)
		speed = 10;
	else speed = 1;
}

void ModulePlayer::processInput() {
	switch (state) {
	case MOVING_DOWN:
		shooting_position = { 2,16 };
		shooting_angle = 180;
		current_animation = &backward;
		fire = App->particles->fire_down;
		break;
	case MOVING_UP:
		shooting_position = { 10,2 };
		shooting_angle = 0;
		current_animation = &forward;
		fire = App->particles->fire_up;
		break;
	case MOVING_RIGHT:
		shooting_position = { 20,8 };
		shooting_angle = 90;
		current_animation = &right;
		fire = App->particles->fire_right;
		break;
	case MOVING_LEFT:
		shooting_position = { 0,8 };
		shooting_angle = -90;
		current_animation = &left;
		fire = App->particles->fire_left;
		break;
	case MOVING_DOWN_RIGHT:
		shooting_position = { 15,17 };
		shooting_angle = 135;
		current_animation = &down_right;
		fire = App->particles->fire_downright;
		break;
	case MOVING_DOWN_LEFT:
		shooting_position = { 2,15 };
		shooting_angle = -135;
		current_animation = &down_left;
		fire = App->particles->fire_downleft;
		break;
	case MOVING_UP_LEFT:
		shooting_position = { 0,4 };
		shooting_angle = -45;
		current_animation = &up_left;
		fire = App->particles->fire_upleft;
		break;
	case MOVING_UP_RIGHT:
		shooting_position = { 15,5 };
		shooting_angle = 45;
		current_animation = &up_right;
		fire = App->particles->fire_upright;
		break;
	case IDLE:
		if (!bthrowing)
		{
			current_animation->speed = 0.0f;
		}
		return;
	}


	position.x += speed * sinf(shooting_angle * M_PI / 180);
	position.y -= speed * cosf(shooting_angle * M_PI / 180);
}

void ModulePlayer::OnCollision(Collider* self, Collider* other) {
	switch (other->type) {
	case COLLIDER_WALL:
		wallCollision();
		break;
	case COLLIDER_WATER:
		waterCollision();
		break;
	case COLLIDER_ENEMY:
	case COLLIDER_ENEMY_SHOT:
		enemyCollision();
	}
}

void ModulePlayer::wallCollision() {
	position = prev_position;
}

void ModulePlayer::waterCollision() {
	Drown();
}

void ModulePlayer::enemyCollision() {
	if (state != DEAD) {
		state = DEAD;
		current_animation = &death;
		if (current_animation->Finished())
			current_animation->Reset();
	}
}

void ModulePlayer::Drown() {
	if (state != DEAD) {
		state = DEAD;
		current_animation = &drown;
		if (current_animation->Finished())
			current_animation->Reset();
	}
}

PLAYER_STATE operator |(PLAYER_STATE p, PLAYER_STATE s) {
	PLAYER_STATE ret = static_cast<PLAYER_STATE>((int)p | (int)s);
	return ret;
}