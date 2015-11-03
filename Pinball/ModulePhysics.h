#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

// type of body
enum body_type
{
	b_dynamic,
	b_static,
	b_kinematic
};

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	//PhysBody() : listener(NULL), body(NULL)
	//{}
	PhysBody(b2Body* body, const SDL_Rect& rect, body_type type);
	~PhysBody();

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;
	double GetAngle() const;
	void Force(int degrees);


public:
	int width, height;
	b2Body* body;
	Module* listener;

private:

	SDL_Rect rect;
	body_type type;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* AddBody(int x, int y, int diameter, body_type type = b_dynamic, float density = 1.0f, float restitution = 0.0f, bool ccd = false, bool isSensor = false);
	PhysBody* AddBody(const SDL_Rect& rect, int* points, uint count, body_type type = b_dynamic, float density = 1.0f, float restitution = 0.0f, bool isSensor = false);
	PhysBody* AddEdge(const SDL_Rect& rect, int* points, uint count);
	/*PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody* CreateStaticRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size);
	PhysBody* CreateChainStatic(int x, int y, int* points, int size);*/
	
	
	void CreateRevoluteJoin(int x1, int y1, int x2, int y2, PhysBody* bodyA, PhysBody* bodyB, int max_angle, int min_angle);
	//b2PrismaticJoint* CreatePrismaticJoint(PhysBody* bodyA, PhysBody* bodyB);
	void DestroyBody(PhysBody* body);
	// b2ContactListener ---
	void BeginContact(b2Contact* contact);


private:

	bool debug;
	b2World* world;
	p2List<PhysBody*> bodies;
	//b2MouseJoint* mouse_joint;
	//b2Body* ground;
public:
	//PhysBody* ground1;
};