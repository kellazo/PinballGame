#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//circle = box = rick = NULL;
	//ray_on = false;
	//sensed = false;
	pinball_empty = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	//proba = NULL;
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	//circle = App->textures->Load("pinball/wheel1.png"); 
	//box = App->textures->Load("pinball/box.png");
	//rick = App->textures->Load("pinball/rick_head.png");
	//bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	pinball_empty = App->textures->Load("pinball/pinball_empty.png");
	// Pivot 0, 0
	int pinball[138] = {
		334, 826,
		333, 813,
		360, 789,
		512, 739,
		515, 481,
		498, 480,
		460, 449,
		458, 433,
		514, 379,
		513, 246,
		500, 210,
		480, 170,
		453, 132,
		420, 100,
		388, 82,
		348, 66,
		300, 55,
		249, 60,
		199, 70,
		155, 92,
		120, 121,
		83, 158,
		60, 205,
		53, 203,
		67, 167,
		107, 121,
		145, 86,
		188, 64,
		260, 49,
		333, 53,
		378, 72,
		410, 85,
		433, 100,
		466, 138,
		493, 173,
		508, 209,
		523, 246,
		523, 717,
		571, 717,
		569, 266,
		547, 206,
		529, 160,
		504, 118,
		472, 83,
		427, 53,
		376, 33,
		306, 15,
		247, 13,
		189, 29,
		146, 48,
		86, 78,
		40, 129,
		9, 186,
		4, 212,
		25, 253,
		26, 266,
		12, 288,
		11, 353,
		26, 390,
		47, 406,
		72, 413,
		94, 440,
		94, 450,
		39, 486,
		39, 737,
		190, 791,
		219, 815,
		220, 833,
		218, 833
	};
	App->physics->AddEdge({ 0, 0, 585, 1024 }, pinball, 138);
	//App->physics->CreateChainStatic(0, 0, pinball, 138);

	//flippers = App->textures->Load("pinball/flippers.png");

	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	//circles.add(App->physics->CreateCircle(544, 602, 11));

	//Prismatic joint
	//boxes.add(App->physics->CreateRectangle(544, 613, 37, 19));
	//BoxUp = App->physics->CreateRectangle(544, 613, 37, 19);
	//StaticBox= App->physics->CreateStaticRectangle(544, 500, 37, 19);
	

	//proba = App->physics->CreatePrismaticJoint(BoxUp, StaticBox);

	//definim una caixa qualsevol
	//caixa = App->physics->CreateRectangle(300,400,125,25);
	//ara crear revolute join -> enganxar en cordenades de body que parteix des del centre i posem posicio a la esquina que es la meitat de width dividit per la meitat de heihgt
	//segon dir a quin punt de lescenari en el anchor nomes si estas utilitzant una chain pk en aquest cas les chain ocupen tot l'escenari
	//App->physics->CreateRevoluteJoin(62, 12, 300, 400, caixa, App->physics->ground1);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(pinball_empty);
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
		App->renderer->Blit(pinball_empty, 0, 0);
		//App->renderer->Blit(flippers,0,0);
		//int box_x, box_y;
		//BoxUp->GetPosition(box_x, box_y);
		//App->renderer->Blit(box, box_x, box_y);

	/* ******************

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		proba->EnableMotor(false);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP){

		proba->EnableMotor(true);
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 11));
		circles.getLast()->data->listener = this;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		caixa->Force(caixa->body, 32 * DEGTORAD);
		LOG("aplicant força");
	}


	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	****************************+
	*/

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	//App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
