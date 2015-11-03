#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleRender.h"




ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	ball.graphic = App->textures->Load("pinball/wheel1.png");
	flipper1.graphic = App->textures->Load("pinball/f1.png");
	flipper2.graphic = App->textures->Load("pinball/f2.png");
	box.graphic = App->textures->Load("pinball/box.PNG");


	ball.body = App->physics->AddBody(563, 582, 28, b_dynamic, 1.0f, 0.3f, true);
	ball.body->listener = this;

	// Pivot 0, 0
	int f1[18] = {
		10, 2,
		22, 1,
		90, 62,
		91, 70,
		87, 74,
		76, 73,
		2, 23,
		2, 11,
		10, 2
	};

	flipper1.body = App->physics->AddBody({ 250, 655, 0, 0 }, f1, 17, b_dynamic);
	flipper1_wheel = App->physics->AddBody(172, 685, 10, b_static);
	App->physics->CreateRevoluteJoin(14, 17, 0, 0, flipper1.body, flipper1_wheel, 30, -30);

	// Pivot 0, 0
	int f2[18] = {
		66, 3,
		82, 1,
		90, 12,
		90, 21,
		14, 74,
		4, 74,
		0, 68,
		0, 61,
		66, 3
	};
	flipper2.body = App->physics->AddBody({ 370, 655, 0, 0 }, f2, 17, b_dynamic);
	flipper2_wheel = App->physics->AddBody(392, 685, 10, b_static);
	App->physics->CreateRevoluteJoin(80, 17, 0, 0, flipper2.body, flipper2_wheel, 30, -30);

	//Prismatic joint
	box.body = App->physics->AddBody({ 550, 620, 30, 20 }, b_dynamic);
	box_wheel = App->physics->AddBody(550, 630, 2, b_static);
	App->physics->CreatePrismaticJoint(box.body, box_wheel);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;

	App->textures->Unload(ball.graphic);
	App->textures->Unload(flipper1.graphic);
	App->textures->Unload(flipper2.graphic);
	App->textures->Unload(box.graphic);


	App->physics->DestroyBody(ball.body);
	App->physics->DestroyBody(flipper1.body);
	App->physics->DestroyBody(flipper2.body);
	App->physics->DestroyBody(box.body);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	static float spring_push = 0.0f;

	
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flipper1.body->Force(-360);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flipper2.body->Force(360);
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		spring_push += 175.0f;
		box.body->Push(0, spring_push);
	}
	else
		spring_push = 0.0f;


	int x, y;

	ball.body->GetPosition(x, y);
	App->renderer->Blit(ball.graphic, x-10, y-10, NULL, 1.0f);//, ball.body->GetAngle());

	
	
	flipper1.body->GetPosition(x, y);
	App->renderer->Blit(flipper1.graphic, x, y, NULL, 1.0f, flipper1.body->GetAngle(),0,0);// , flipper1.body->GetAngle(), 0, 0);

	flipper2.body->GetPosition(x, y);
	App->renderer->Blit(flipper2.graphic, x, y, NULL, 1.0f, flipper2.body->GetAngle(),0,0);// , flipper1.body->GetAngle(), 0, 0);

	box.body->GetPosition(x, y);
	App->renderer->Blit(box.graphic, x, y, NULL, 1.0f, box.body->GetAngle(),0,0);
	return UPDATE_CONTINUE;
}



