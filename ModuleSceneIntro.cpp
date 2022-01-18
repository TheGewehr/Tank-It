#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	Cube* c = new Cube(vec3(100, 10, 100), 0.0f);

	//const vec3& _size, float mass
	c->SetPos(0, 0, 3);
	
	c->SetRotation(10, vec3(0, 0, 1));

	c->SetRotation(10, vec3(0.0f, 1.0f, 0.0f));
	PhysBody3D phys = *App->physics->AddBody(*c, 0.0f);
	phys.SetBodyCube(c, 0.0f);
	//map.PushBack(c);
	world.add(phys);
	//PhysBody3D i = world->getFirst();

	//delete c;
	//delete phys;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	//phys->parentPrimitive->Render();

	//for (int i = 0; i < world.count(); i++)
	//{
		//world[i].parentPrimitive->Render();
	//	world.atIndex(i).parentPrimitive->Render();
	//}


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

