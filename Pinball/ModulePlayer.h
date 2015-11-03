#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"

class PhysBody;

struct Object
{
	SDL_Texture* graphic;
	PhysBody* body;
	uint fx;

	Object() : graphic(NULL), body(NULL)
	{}
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Object ball;
	Object flipper1;
	Object flipper2;
	Object box;

	PhysBody* box_wheel;
	PhysBody* flipper1_wheel;
	PhysBody* flipper2_wheel;
	//PhysBody* spring_wheel;


	//PhysBody* sensor1;

};