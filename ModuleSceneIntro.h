#pragma once
#include "Application.h"
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "p2List.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;
class Cube;

enum class ORIENTATION
{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST,
	NORTHEAST,
	NORTHWEST,
	SOUTHEAST,
	SOUTHWEST
};


class ModuleSceneIntro : public Module
{
public:

	ModuleSceneIntro(Application* app, bool start_enabled = true);

	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	
	void CreateDragon(const float& x, const float& y, const float& z, const float& width, const float& length, vec3 vec3, float mass, ORIENTATION orientation);

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	PhysBody3D AddToWorld_(vec3 col, vec3 pos, bool mass);
public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube *p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	p2List<PhysBody3D> world;
	p2List<Cube*> primList;
	bool win_con = false;
	vec3 win;
	vec3 win_s;
};
