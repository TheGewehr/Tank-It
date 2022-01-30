#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"
#include "ModulePlayer.h"
#include "Bullet/include/btBulletDynamicsCommon.h"


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

	c->SetPos(0, 0, 3);
	
	c->SetRotation(10, vec3(0, 0, 1));

	c->SetRotation(10, vec3(0.0f, 1.0f, 0.0f));

	PhysBody3D phys = *App->physics->AddBody(*c, 0.0f);
	phys.SetBodyCube(c, 0.0f);
	
	phys.body->setUserPointer(&phys);
	//map.PushBack(c);
	world.add(phys);
	primList.add(c);
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

	//for (int i = 0; i < primList.count(); i++)
	//{
		
		//world.atIndex(i).GetTransform(world.atIndex(i).parentPrimitive->transform);
		//world.atIndex(i).SetTransform(world.atIndex(i).parentPrimitive->transform);
		//world.atIndex(i).parentPrimitive->color = Blue;
		//world.atIndex(i).parentPrimitive->Render();

		//primList.atIndex(i).body.GetTransform(primList.atIndex(i).transform);
		
		//track[n].GetTransform(&track[n].parentPrimitive->transform);

		//track[n].parentPrimitive->Render();
		//primList.atIndex(i).body.body->getWorldTransform().getOpenGLMatrix(&primList.atIndex(i).transform);
		//PhysBody3D* dummy = nullptr;

		
		//dummy->GetTransform(&dummy->parentPrimitive->transform);
		//dummy->body.GetTransform(&dummy->transform);
		//dummy->parentPrimitive->Render();

		//primList.atIndex(i).color = Black;
		//primList.atIndex(i).Render();
		//vehicle_t->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);
	//}


	
	

	for (p2List_item<Cube*>* control = primList.getFirst(); control != nullptr; control = control->next)
	{
		control->data->Render();

	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

