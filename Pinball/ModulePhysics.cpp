#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

PhysBody::PhysBody(b2Body* body, const SDL_Rect& rect, body_type type) : body(body), rect(rect), type(type), listener(NULL)
{}

PhysBody::~PhysBody()
{
	body->GetWorld()->DestroyBody(body);
	body = NULL;
	listener = NULL;
}

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
//	mouse_joint = NULL;
	debug = true;
	
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}
// Called before render is available
bool ModulePhysics::Init()
{
	LOG("Creating Physics environment");
	bool ret = true;

	return ret;
}
bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);
	
	// needed to create joints like mouse joint
	//b2BodyDef bd;
	//ground = world->CreateBody(&bd);

	/*int pinball[138] = {
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
	};*/
	//CreateChainStatic(0, 0, pinball, 138);
	//ground1 = CreateChainStatic(0, 0, pinball, 138);

	/*
	int pinball_structure_up[32] = {
		120, 223,
		130, 229,
		232, 233,
		258, 216,
		314, 217,
		328, 232,
		439, 231,
		449, 219,
		443, 194,
		412, 149,
		362, 115,
		314, 105,
		253, 105,
		198, 119,
		151, 151,
		121, 209
	};
	CreateChainStatic(0, 0,pinball_structure_up, 32);
	
	int left_structures[12] = {
		168, 670,
		158, 690,
		83, 645,
		83, 500,
		92, 507,
		95, 622
	};
	CreateChainStatic(0, 0, left_structures, 12);

	int left_triangles[12] = {
		184, 621,
		140, 537,
		129, 529,
		129, 601,
		172, 637,
		181, 637
	};
	CreateChainStatic(0, 0, left_triangles, 12);
	int flippers[28] = {
		159, 686,
		156, 670,
		169, 659,
		184, 668,
		200, 682,
		218, 699,
		241, 717,
		246, 722,
		246, 730,
		243, 734,
		230, 733,
		216, 724,
		198, 713,
		160, 686
	};
	CreateChainStatic(0, 0, flippers, 28);


	b2Vec2 p1(-2.0f, 0.0f);

	
	bd.type = b2_dynamicBody;

	bd.position = p1;
	b2Body* leftFlipper = world->CreateBody(&bd);

	

	b2PolygonShape box;
	box.SetAsBox(1.75f, 0.1f);

	b2FixtureDef fd;
	fd.shape = &box;
	fd.density = 1.0f;

	leftFlipper->CreateFixture(&fd);

	b2RevoluteJointDef jd;
	jd.bodyA = ground;
	jd.localAnchorB.SetZero();
	jd.enableMotor = true;
	jd.maxMotorTorque = 1000.0f;
	jd.enableLimit = true;

	b2RevoluteJoint*  m_leftJoint = NULL;

	jd.motorSpeed = 0.0f;
	jd.localAnchorA = p1;
	jd.bodyB = leftFlipper;
	jd.lowerAngle = -30.0f * b2_pi / 180.0f;
	jd.upperAngle = 5.0f * b2_pi / 180.0f;
	m_leftJoint = (b2RevoluteJoint*)world->CreateJoint(&jd);

	++++++++++++++++++++++++++++++
	*/
	

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.
	world->Step(timeStep, velocityIterations, positionIterations);

	// Check for collisions on sensors (collision listener does not work for sensors)
	
	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}
	
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{


	//b2Vec2 mouse_position;
	//PhysBody* body_clicked = NULL;


	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		uint8 green = b->GetType() == b2BodyType::b2_staticBody ? 255 : 0;
		uint8 blue = b->GetType() == b2BodyType::b2_kinematicBody ? 255 : 0;

		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch (f->GetType())
			{
				// Draw circles ------------------------------------------------
			case b2Shape::e_circle:
			{
				b2CircleShape* shape = (b2CircleShape*)f->GetShape();
				b2Vec2 pos = f->GetBody()->GetPosition();
				App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
			}
			break;

			// Draw polygons ------------------------------------------------
			case b2Shape::e_polygon:
			{
				b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
				int32 count = polygonShape->GetVertexCount();
				b2Vec2 prev, v;

				for (int32 i = 0; i < count; ++i)
				{
					v = b->GetWorldPoint(polygonShape->GetVertex(i));
					if (i > 0)
						App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

					prev = v;
				}

				v = b->GetWorldPoint(polygonShape->GetVertex(0));
				App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
			}
			break;

			// Draw chains contour -------------------------------------------
			case b2Shape::e_chain:
			{
				b2ChainShape* shape = (b2ChainShape*)f->GetShape();
				b2Vec2 prev, v;

				for (int32 i = 0; i < shape->m_count; ++i)
				{
					v = b->GetWorldPoint(shape->m_vertices[i]);
					if (i > 0)
						App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
					prev = v;
				}

				v = b->GetWorldPoint(shape->m_vertices[0]);
				App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
			}
			break;

			// Draw a single segment(edge) ----------------------------------

			case b2Shape::e_edge:
			{
				b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
				b2Vec2 v1, v2;

				v1 = b->GetWorldPoint(shape->m_vertex0);
				v1 = b->GetWorldPoint(shape->m_vertex1);
				App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
			}
			break;
			}
			/*
			// TODO 1: If mouse button 1 is pressed ...
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				mouse_position.x = PIXEL_TO_METERS(App->input->GetMouseX());
				mouse_position.y = PIXEL_TO_METERS(App->input->GetMouseY());

				// test if the current body contains mouse position
				if (f->GetShape()->TestPoint(b->GetTransform(), mouse_position) == true)
				{

					body_clicked = (PhysBody*)f->GetBody()->GetUserData();
					LOG("HAS FET CLICK AL OBJECTE");
					//break;
				}
			}*/


		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property
	/*if (body_clicked != NULL)
	{
		b2MouseJointDef def;
		def.bodyA = ground;
		def.bodyB = body_clicked->body;
		def.target = mouse_position;
		def.dampingRatio = 0.5f;
		def.frequencyHz = 2.0f;
		def.maxForce = 100.0f * body_clicked->body->GetMass();

		mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);

	}
	if (mouse_joint != NULL && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)

	{
		// TODO 3: If the player keeps pressing the mouse button, update
		// target position and draw a red line between both anchor points
		b2Vec2 posA, posB;
		posA = mouse_joint->GetAnchorA();
		//posB = mouse_joint->GetAnchorB();
		posB.x = App->input->GetMouseX();
		posB.y = App->input->GetMouseY();
		App->renderer->DrawLine(METERS_TO_PIXELS(posA.x), METERS_TO_PIXELS(posA.y), METERS_TO_PIXELS(posB.x), METERS_TO_PIXELS(posB.y), 100, 150, 255);

	}*/
	// TODO 4: If the player releases the mouse button, destroy the joint
	//if (mouse_joint != NULL && App->input->GetMouseButton())

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	p2List_item<PhysBody*>* item = bodies.getFirst();

	while (item != NULL)
	{
		delete item->data;
		item = item->next;
	}

	bodies.clear();
	// Delete the whole physics world!
	delete world;

	return true;
}

PhysBody* ModulePhysics::AddBody(const SDL_Rect& rect, body_type type, float density, float restitution, bool ccd, bool isSensor)
{
	b2BodyDef body;

	switch (type)
	{
	case b_static:
		body.type = b2_staticBody;
		break;

	case b_kinematic:
		body.type = b2_kinematicBody;
		break;

	default:
		body.type = b2_dynamicBody;
		break;
	}

	body.position.Set(PIXEL_TO_METERS(rect.x), PIXEL_TO_METERS(rect.y));
	body.angle = 0.0f;
	body.bullet = ccd;

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box_shape;
	box_shape.SetAsBox(PIXEL_TO_METERS(rect.w / 2), PIXEL_TO_METERS(rect.h / 2));

	b2FixtureDef box_fixture;
	box_fixture.shape = &box_shape;
	box_fixture.density = density;
	box_fixture.restitution = restitution;
	box_fixture.isSensor = isSensor;

	b->CreateFixture(&box_fixture);

	PhysBody* ret = new PhysBody(b, rect, type);
	bodies.add(ret);

	b->SetUserData(ret);

	return ret;
}

PhysBody* ModulePhysics::AddBody(int x, int y, int diameter, body_type type, float density, float restitution, bool ccd, bool isSensor)
{
	b2BodyDef body;

	switch (type)
	{
	case b_static:
		body.type = b2_staticBody;
		break;

	case b_kinematic:
		body.type = b2_kinematicBody;
		break;

	default:
		body.type = b2_dynamicBody;
		break;
	}

	float radius = PIXEL_TO_METERS(diameter) * 0.5f;

	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.angle = 0.0f;
	body.bullet = ccd;

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = radius;

	b2FixtureDef box_fixture;
	box_fixture.shape = &shape;
	box_fixture.density = density;
	box_fixture.restitution = restitution;
	box_fixture.isSensor = isSensor;

	b->CreateFixture(&box_fixture);

	PhysBody* ret = new PhysBody(b, { x, y, diameter, diameter }, type);
	bodies.add(ret);

	b->SetUserData(ret);

	return ret;
}

PhysBody* ModulePhysics::AddBody(const SDL_Rect& rect, int* points, uint count, body_type type, float density, float restitution, bool isSensor)
{
	b2BodyDef body;

	switch (type)
	{
	case b_static:
		body.type = b2_staticBody;
		break;

	case b_kinematic:
		body.type = b2_kinematicBody;
		break;

	default:
		body.type = b2_dynamicBody;
		break;
	}

	body.position.Set(PIXEL_TO_METERS(rect.x), PIXEL_TO_METERS(rect.y));
	body.angle = 0.0f;

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape shape;
	b2Vec2* p = new b2Vec2[count / 2];
	for (uint i = 0; i < count / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.Set(p, count / 2);

	b2FixtureDef box_fixture;
	box_fixture.shape = &shape;
	box_fixture.density = density;
	box_fixture.restitution = restitution;
	box_fixture.isSensor = isSensor;

	b->CreateFixture(&box_fixture);

	PhysBody* ret = new PhysBody(b, { rect.x, rect.y, rect.w, rect.h }, type);
	bodies.add(ret);

	delete[] p;

	b->SetUserData(ret);

	return ret;
}

PhysBody* ModulePhysics::AddEdge(const SDL_Rect& rect, int* points, uint count)
{
	b2BodyDef body;

	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(rect.x), PIXEL_TO_METERS(rect.y));
	body.angle = 0.0f;

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[count / 2];

	for (uint i = 0; i < count / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);// *rect.w;
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);// *rect.h;
	}

	shape.CreateLoop(p, count / 2);

	b2FixtureDef box_fixture;
	box_fixture.shape = &shape;

	b->CreateFixture(&box_fixture);

	PhysBody* ret = new PhysBody(b, rect, b_static);
	bodies.add(ret);

	delete[] p;

	b->SetUserData(ret);

	return ret;
}

/*    ++++++++++++++++++++++++++++++++++++++++++++++++++


PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;

	return pbody;
}


PhysBody* ModulePhysics::CreateStaticRectangle(int x, int y, int width, int height){
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.restitution = 0;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

PhysBody* ModulePhysics::CreateChainStatic(int x, int y, int* points, int size)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for (uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->width = pbody->height = 0;
	return pbody;
}
*/
//li passem els punts de cada enclaje segons el body, i ha de rebre quins son
void ModulePhysics::CreateRevoluteJoin(int x1, int y1, int x2, int y2, PhysBody* bodyA, PhysBody* bodyB, int max_angle, int min_angle)
{
	//

	b2RevoluteJointDef jd;

	jd.bodyA = bodyA->body;
	jd.bodyB = bodyB->body;
	//enganchem ancors
	//A: localAnchor  reben un vector, pertam les cordenades pasarles a b2Vec2 i pasarles a metres
	b2Vec2 AnchorA(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	b2Vec2 AnchorB(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	jd.localAnchorA = AnchorA;
	jd.localAnchorB = AnchorB;
	//Amb aixo ja tenim les posicions, ara fem les propietats especifiques del revolute joint

	//Especificar que vull un limit
	//jd.enableLimit = true;
	//especificar quin es el limit de dalt i el de baix ( tambe tenim la opcio de posaro com a parametre
	//i passaro a radiants
	//jd.upperAngle = angle;
	//jd.lowerAngle = angle_max;
	//Especificar si vull motor;
	//jd.enableMotor = true;
	//Torque maxim
	//jd.maxMotorTorque = 1000.0f;
	//velocitat angular
	//jd.motorSpeed = -360 * DEGTORAD;

	//per cambiar velocitat d'un joint un cop creat, s'utilitza una funci� que es diu SetMotorSpeed(), per arribar, agafes el body (en aquest cas un PhysBody)
	//((b2RevoluteJoint*)pbody->body->GetJointList()->joint)->SetMotorSpeed()


	if (max_angle != INT_MAX && min_angle != INT_MIN)
	{
		jd.enableLimit = true;
		jd.upperAngle = DEGTORAD * max_angle;
		jd.lowerAngle = DEGTORAD * min_angle;
	}


	world->CreateJoint(&jd);


	/*b2RevoluteJoint*  m_leftJoint = NULL;

	jd.motorSpeed = 0.0f;
	jd.localAnchorA = p1;
	jd.bodyB = leftFlipper;
	jd.lowerAngle = -30.0f * b2_pi / 180.0f;
	jd.upperAngle = 5.0f * b2_pi / 180.0f;
	m_leftJoint = (b2RevoluteJoint*)world->CreateJoint(&jd);*/
}

// 

b2PrismaticJoint* ModulePhysics::CreatePrismaticJoint(PhysBody* bodyA, PhysBody* bodyB){
	b2PrismaticJointDef jointD;

	b2Vec2 vector(0.0f, 1.0f);
	jointD.Initialize(bodyA->body, bodyB->body, bodyA->body->GetPosition(), vector);
	jointD.lowerTranslation = -2.0f;
	jointD.upperTranslation = 0.0f;
	jointD.enableLimit = true;
	jointD.maxMotorForce = -90.0f;
	jointD.motorSpeed = -80.0f;
	jointD.enableMotor = true;

	return ((b2PrismaticJoint*) world->CreateJoint(&jointD));
}

void ModulePhysics::DestroyBody(PhysBody* body)
{
	assert(body);
	bodies.del(bodies.findNode(body));
	delete body;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

void PhysBody::Force(int degrees)
{
	
	body->ApplyAngularImpulse(DEGTORAD * degrees, true);
	
}
void PhysBody::Push(float x, float y)
{
	body->ApplyForceToCenter(b2Vec2(x, y), true);
}

double PhysBody::GetAngle() const
{
	return RADTODEG * body->GetAngle();
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}

