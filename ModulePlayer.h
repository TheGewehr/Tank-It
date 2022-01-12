#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;
struct PhysTrack3D;
#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate();
	bool CleanUp();

public:

	PhysTrack3D* vehicle;

	PhysTrack3D* track01;
	float turn;
	float acceleration;
	float brake;
	vec3 size;

	p2List<Primitive*>primitives;
};