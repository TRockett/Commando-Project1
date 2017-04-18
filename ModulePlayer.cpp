#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneGame.h"
#include "ModuleParticles.h"
#include <math.h>
#include "ModuleSound.h"
#include "ModuleCollision.h"


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
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	position.x = SCREEN_WIDTH / 2;
	position.y = 190;
	shooting_angle = 0;
	shooting_position = { 9,1 };
	collider = App->collision->AddCollider({ (int)position.x, (int)position.y, 13, 23 }, COLLIDER_PLAYER, this);
	LOG("Loading player textures");
	graphics = App->textures->Load("Images/sprites.png"); 

	current_animation= &forward;

	shoot = App->sound->LoadSound("SoundFX/Commando (shoot)_03.wav");

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
	state = IDLE;
	current_animation->speed = 0.15f;
	shooting = false;
	grenade = false;
	checkInput();
	processInput();

	// Draw everything --------------------------------------
	AnimationFrame frame =  current_animation->GetCurrentFrame();
	iPoint camera = App->scene_game->getLevelDimensions();

	if (shooting) {
		App->sound->PlaySound(shoot, 0);
		Particle bullet = App->particles->bullet;
		bullet.speed = { (int)(PLAYER_BULLET_SPEED * sinf(shooting_angle * M_PI / 180)), (int)(-PLAYER_BULLET_SPEED * cosf(shooting_angle * M_PI / 180)) };
		App->particles->AddParticle(bullet, position.x + shooting_position.x, position.y + shooting_position.y, COLLIDER_PLAYER_SHOT);
		//Particle delay doesnt work
		//App->particles->AddParticle(bullet, position.x + shooting_position.x, position.y + shooting_position.y, COLLIDER_PLAYER_SHOT, 500);
		//App->particles->AddParticle(bullet, position.x + shooting_position.x, position.y + shooting_position.y, COLLIDER_PLAYER_SHOT, 1000);
	}
	if (grenade)
	{
		Particle grenade = App->particles->grenade;
		grenade.speed = {((int)0),((int)-20)};
	}
	int margin = MAX(200, position.y);
	collider->rect = { (int)position.x - frame.pivot.x, (int)position.y - frame.pivot.y, frame.rect.w, frame.rect.h };
	App->render->camera.y = (-position.y + margin) * SCREEN_SIZE;
	App->render->Blit(graphics, (position.x - frame.pivot.x), (position.y - frame.pivot.y), &frame.rect);

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
		grenade = true;
	}
}

void ModulePlayer::processInput() {
	switch (state) {
	case MOVING_DOWN:
		shooting_position = { 2,16 };
		shooting_angle = 180;
		current_animation = &backward;
		break;
	case MOVING_UP:
		shooting_position = { 10,2 };
		shooting_angle = 0;
		current_animation = &forward;
		break;
	case MOVING_RIGHT:
		shooting_position = { 20,8 };
		shooting_angle = 90;
		current_animation = &right;
		break;
	case MOVING_LEFT:
		shooting_position = { 0,8 };
		shooting_angle = -90;
		current_animation = &left;
		break;
	case MOVING_DOWN_RIGHT:
		shooting_position = { 15,17 };
		shooting_angle = 135;
		current_animation = &down_right;
		break;
	case MOVING_DOWN_LEFT:
		shooting_position = { 2,15 };
		shooting_angle = -135;
		current_animation = &down_left;
		break;
	case MOVING_UP_LEFT:
		shooting_position = { 0,4 };
		shooting_angle = -45;
		current_animation = &up_left;
		break;
	case MOVING_UP_RIGHT:
		shooting_position = { 15,5 };
		shooting_angle = 45;
		current_animation = &up_right;
		break;
	case IDLE:
		current_animation->speed = 0.0f;
		return;
	}

	position.x += speed * sinf(shooting_angle * M_PI / 180);
	position.y -= speed * cosf(shooting_angle * M_PI / 180);
}

void ModulePlayer::OnCollision(Collider* self, Collider* other) { //Not final version
	switch (state) {
	case MOVING_DOWN:
		position.y -= speed;
		break;
	case MOVING_UP:
		position.y += speed;
		break;
	case MOVING_RIGHT:
		position.x -= speed;
		break;
	case MOVING_LEFT:
		position.x += speed;
		break;
	case MOVING_DOWN_RIGHT:
		position.x -= speed * sinf(45 * M_PI / 180);
		position.y -= speed * cosf(45 * M_PI / 180);
		break;
	case MOVING_DOWN_LEFT:
		position.x += speed * sinf(45 * M_PI / 180);
		position.y -= speed * cosf(45 * M_PI / 180);
		break;
	case MOVING_UP_LEFT:
		position.x += speed * sinf(45 * M_PI / 180);
		position.y += speed * cosf(45 * M_PI / 180);
		break;
	case MOVING_UP_RIGHT:
		position.x -= speed * sinf(45 * M_PI / 180);
		position.y += speed * cosf(45 * M_PI / 180);
		break;
	}
}

PLAYER_STATE operator |(PLAYER_STATE p, PLAYER_STATE s) {
	PLAYER_STATE ret = static_cast<PLAYER_STATE>((int)p | (int)s);
	return ret;
}