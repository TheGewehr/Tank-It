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

	c->SetPos(0, 0, 45);
	
	c->SetRotation(-17, vec3(1, 0, 0));

	//c->SetRotation(10, vec3(0.0f, 1.0f, 0.0f));

	PhysBody3D phys = *App->physics->AddBody(*c, 0.0f);
	phys.SetBodyCube(c, 0.0f);
	
	phys.body->setUserPointer(&phys);
	//map.PushBack(c);
	world.add(phys);
	primList.add(c);
	//PhysBody3D i = world->getFirst();

	//delete c;
	//delete phys;

	AddToWorld_(vec3(16, 5, 60), vec3(0, 16, 130), false);
	CreateDragon(4, 19, 101, 1, 30, vec3 (1, 2, 1), 0.0f, ORIENTATION::EAST);
	CreateDragon(-4, 19, 159, 1, 28, vec3(1, 2, 1), 0.0f, ORIENTATION::WEST);

	AddToWorld_(vec3(200, 5, 20), vec3(-92, 16, 170), false);
	CreateDragon(-34, 19, 176, 1, 21, vec3(1, 2, 1), 0.0f, ORIENTATION::NORTH);
	CreateDragon(-8, 19, 164, 1, 14, vec3(1, 2, 1), 0.0f, ORIENTATION::SOUTH);
	

	AddToWorld_(vec3(1, 5, 1), vec3(1, 2, -10), false);
	
	AddToWorld_(vec3(50, 5, 40), vec3(-250, 41, 170), false);
	//AddToWorld_(vec3(124, 5, 20), vec3-104 - 25, 20, 170));
		
	Cube* c4 = new Cube(vec3(18, 5, 20), 0.0f);

	c4->SetPos(-115 - 30 -50, 19, 170);
	c4->SetRotation(-30, vec3(0, 0, 1));
	PhysBody3D phys02 = *App->physics->AddBody(*c4, 0.0f);
	phys02.SetBodyCube(c4, 0.0f);
	phys02.body->setUserPointer(&phys02);
	//map.PushBack(c);

	world.add(phys02);
	primList.add(c4);

	Cube* c5 = new Cube(vec3(18, 5, 20), 0.0f);

	c5->SetPos(-115 - 35 -50, 26, 170);
	c5->SetRotation(-60, vec3(0, 0, 1));
	PhysBody3D phys03 = *App->physics->AddBody(*c5, 0.0f);
	phys03.SetBodyCube(c5, 0.0f);
	phys03.body->setUserPointer(&phys03);
	//map.PushBack(c);

	world.add(phys03);
	primList.add(c5);

	Cube* c6 = new Cube(vec3(18, 5, 20), 0.0f);

	c6->SetPos(-115 - 39 -50, 33, 170);
	c6->SetRotation(-80, vec3(0, 0, 1));
	PhysBody3D phys04 = *App->physics->AddBody(*c6, 0.0f);
	phys04.SetBodyCube(c6, 0.0f);
	phys04.body->setUserPointer(&phys04);
	//map.PushBack(c);

	world.add(phys04);
	primList.add(c6);

	Cube* c7 = new Cube(vec3(18, 5, 20), 0.0f);

	c7->SetPos(-115 - 33 - 50, 50, 170);
	c7->SetRotation(-50, vec3(0, 0, 1));
	PhysBody3D phys05 = *App->physics->AddBody(*c7, 0.0f);
	phys05.SetBodyCube(c7, 0.0f);
	phys05.body->setUserPointer(&phys05);
	//map.PushBack(c);

	
	world.add(phys05);
	primList.add(c7);

	PhysBody3D* aux_a = new PhysBody3D[14];
	
	for (int i = 0; i < 14; i++)
	{
		if (i == 0 || i == 13)
		{
			aux_a[i] = AddToWorld_(vec3(8, 2, 30), vec3(-275 - (i * 9), 41, 170), false);
		}
		else
		{
			aux_a[i] = AddToWorld_(vec3(8, 2, 30), vec3(-275 - (i * 10), 41, 170), true);
		}
		
		
	}
	
	for (int i = 0; i < 13; i++)
	{
		App->physics->AddConstraintHinge(aux_a[i], aux_a[i+1],
			vec3(-4, 0, 0), vec3(4, 0, 0), vec3(0, 0, 1), vec3(0, 0, 1));
	}
	
	win = { -383, 42, 170
	};
	win_s = { 20, 20, 20 };
	//->SetPos(-300, 45, 170);
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

	vec3 player_pos = App->player->vehicle->GetPosition();
	
	if (player_pos.x < win.x + win_s.x &&
		player_pos.x > win.x - win_s.x &&
		player_pos.y < win.y + win_s.y &&
		player_pos.y > win.y - win_s.y &&
		player_pos.z < win.z + win_s.z &&
		player_pos.z > win.z - win_s.z)
	{
		win_con = true;
	};
	
	

	for (p2List_item<PhysBody3D>* control = world.getFirst(); control != nullptr; control = control->next)
	{

		control->data.GetTransform(&control->data.parentPrimitive->transform);
		
		
		control->data.parentPrimitive->Render();
		
	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::CreateDragon(const float& x, const float& y, const float& z, const float& width, const float& length, vec3 vec3_, float mass, ORIENTATION orientation)
{
	vec3 vector = { vec3_.x, vec3_.y / 2, vec3_.x };
	vec3 vector_ = { vec3_.x, vec3_.y * 2, vec3_.x };

	Cube* c1 = new Cube(vector, mass);
	Cube* c2 = new Cube(vec3_, mass);
	Cube* c3 = new Cube(vector_, mass);
	

	for (int i = 0; i < length; i++) {
		

		switch (orientation)
		{
		case ORIENTATION::NORTH:
			c1->SetPos(x + (i * (width + vec3_.x)), y - vector.y/2, z);
			c2->SetPos(x + (i * (width + vec3_.x) + vec3_.x), y, z + vec3_.z + 0.5);
			c3->SetPos(x + (i * (width + vec3_.x)), y + vector_.y/4, z + 2*vec3_.z + 1);
			break;
		case ORIENTATION::SOUTH:
			c1->SetPos(x - (i * (width + vec3_.x)), y - vector.y / 2, z);
			c2->SetPos(x - (i * (width + vec3_.x) + vec3_.x), y, z - vec3_.z - 0.5);
			c3->SetPos(x - (i * (width + vec3_.x)), y + vector_.y / 4, z - 2 * vec3_.z - 1);
			break;
		case ORIENTATION::EAST:
			c1->SetPos(x, y - vector.y / 2, z + (i * (width + vec3_.z)));
			c2->SetPos(x + vec3_.x + 0.5, y, z + (i * (width + vec3_.z) + vec3_.z));
			c3->SetPos(x + 2 * vec3_.x + 1, y + vector_.y / 4, z + (i * (width + vec3_.z)));
			break;
		case ORIENTATION::WEST:
			c1->SetPos(x, y - vector.y / 2, z - (i * (width + vec3_.z)));
			c2->SetPos(x - vec3_.x - 0.5, y, z - (i * (width + vec3_.z) + vec3_.z));
			c3->SetPos(x - 2 * vec3_.x - 1, y + vector_.y / 4, z - (i * (width + vec3_.z)));
			break;
		case ORIENTATION::NORTHEAST:
			c1->SetPos(x - vec3_.x, y, z + vec3_.x);
			c2->SetPos(x + width - vec3_.x, y, z + vec3_.x);
			break;
		case ORIENTATION::NORTHWEST:
			c1->SetPos(x + vec3_.x, y, z + vec3_.x);
			c2->SetPos(x + width + vec3_.x, y, z + vec3_.x);
			break;
		case ORIENTATION::SOUTHEAST:
			c1->SetPos(x - vec3_.x, y, z - vec3_.x);
			c2->SetPos(x - vec3_.x + width, y, z - vec3_.x);
			break;
		case ORIENTATION::SOUTHWEST:
			c1->SetPos(x + vec3_.x, y, z - vec3_.x);
			c2->SetPos(x + vec3_.x + width, y, z - vec3_.x);
			break;
		default:
			break;
		}
		
		
		
		PhysBody3D phys = *App->physics->AddBody(*c1, 0.0f);
		//phys.SetBodyCube(c1, 0.0f);
		phys.body->setUserPointer(&phys);
		phys.parentPrimitive->color = White;

		PhysBody3D phys2 = *App->physics->AddBody(*c2, 0.0f);
		
		//phys2.SetBodyCube(c2, 0.0f);
		phys2.body->setUserPointer(&phys2);
		phys2.parentPrimitive->color = White;

		PhysBody3D phys3 = *App->physics->AddBody(*c3, 0.0f);

		//phys3.SetBodyCube(c3, 0.0f);
		phys3.body->setUserPointer(&phys3);
		phys3.parentPrimitive->color = White;

		App->scene_intro->world.add(phys);
		App->scene_intro->world.add(phys2);
		App->scene_intro->world.add(phys3);

		App->scene_intro->primList.add(c1);
		App->scene_intro->primList.add(c2);
		App->scene_intro->primList.add(c3);

	}
}


void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

PhysBody3D ModuleSceneIntro::AddToWorld_(vec3 col, vec3 pos, bool mass)
{
	float m;

	if (mass) m = 1.0f;
	else m = 0.0f;
	Cube* c = new Cube(col, m);

	c->SetPos(pos.x, pos.y, pos.z);

	PhysBody3D phys = *App->physics->AddBody(*c, m);
	//phys.SetBodyCube(c, 0.0f);

	phys.body->setUserPointer(&phys);
	//map.PushBack(c);
	world.add(phys);
	primList.add(c);

	return phys;
}

