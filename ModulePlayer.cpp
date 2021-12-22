#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;


	/////////////////////////////////////////////////////////////////////

	App->camera->Move(vec3(0.0f, 1.0f, 1.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	const int SnakeLength = 30;
	const float StartingSize = 0.3f;
	const float SizeIncrement = 0.2f;
	const float BallDistance = 0.3f;

	float XPos = 0.0f;
	float ZPos = 1.0f;
	float Size = StartingSize;

	vec3 size = { 0.1f, 0.1f, 0.5f };

	float section = SnakeLength * 0.25;

	float distanceNodeToNode = (size.x * 0.5) + 0.019f;

	for (int n = 0; n < SnakeLength; n++)
	{
		if (section > n)
		{
			Cube* s = new Cube(size);
			primitives.add(s);
			s->SetPos(XPos + n, 1.f, ZPos);
			s->SetRotation(0, vec3(XPos, 1.f, ZPos));

			XPos += StartingSize + BallDistance;
		}
		else if ((section * 2) > n && n >= section)
		{
			Cube* s = new Cube(size);
			primitives.add(s);
			s->SetPos(XPos + n, 10.f, ZPos);
			s->SetRotation(90, vec3(XPos, 1.f, ZPos));

			ZPos += StartingSize + BallDistance;
		}
		else if ((section * 3) > n && n >= section * 2)
		{
			Cube* s = new Cube(size);
			primitives.add(s);
			s->SetPos(XPos + n, 10.f, ZPos);
			s->SetRotation(180, vec3(XPos, 1.f, ZPos));

			XPos -= StartingSize + BallDistance;
		}
		else
		{
			Cube* s = new Cube(size);
			primitives.add(s);
			s->SetPos(XPos + n, 10.f, ZPos);
			s->SetRotation(270, vec3(XPos, 1.f, ZPos));

			ZPos -= StartingSize + BallDistance;
		}



		//Cube* s = new Cube(size);
		//primitives.add(s);
		//s->SetPos(XPos + 1.5*sin(n), 1.f + 0.5*cos(n), ZPos);
		//s->SetRotation(0, vec3(XPos, 1.f, ZPos));

		//XPos += StartingSize + BallDistance;
		LOG("%f", cos(n));




		if (n == 0)
		{

		}
		else if (n == SnakeLength - 1)
		{
			

			App->physics->AddConstraintHinge(primitives.getLast()->prev->data->body, primitives.getLast()->data->body,
				vec3(distanceNodeToNode, 0, 0), vec3(-distanceNodeToNode, 0, 0), vec3(0, 0, 1), vec3(0, 0, 1));
			App->physics->AddConstraintHinge(primitives.getLast()->data->body, primitives.getFirst()->data->body,
				vec3(distanceNodeToNode, 0, 0), vec3(-distanceNodeToNode, 0, 0), vec3(0, 0, 1), vec3(0, 0, 1));

		}
		else
		{


			App->physics->AddConstraintHinge(primitives.getLast()->prev->data->body, primitives.getLast()->data->body,
				vec3(distanceNodeToNode, 0, 0), vec3(-distanceNodeToNode, 0, 0), vec3(0, 0, 1), vec3(0, 0, 1));


		}

	}

	/////////////////////////////////////////////////////////////////////

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 2, 2);
	car.chassis_offset.Set(0, 0.3, 0);
	car.mass = 500.0f; // 500.0f
	car.suspensionStiffness = 15.88f; // 15.88f  (fuerza de la suspension, fuerza de los springs de suspension)
	car.suspensionCompression = 0.83f; // 0.83f (cuanto mas alto menos se comprime la suspension, limite de compresion)
	car.suspensionDamping = 0.88f; // 0.88f (rigidez de la suspension)
	car.maxSuspensionTravelCm = 1000.0f;// 1000.0f (maxima distancia de movimiento de la suspension)
	car.frictionSlip = 50.5; // 50.5 (friccion de las ruedas)
	car.maxSuspensionForce = 6000.0f; // 6000.0f  (Maxima fuerza que puede ejercer la suspension)

	// Wheel properties ---------------------------------------
	float connection_height = 0.1f; // 1.6f (altura de las ruedas en la suspension)
	float wheel_radius = 0.1f; 
	float wheel_width = 0.1f;
	float suspensionRestLength = 1.0f; //1.2f (ESPACIO DE LA SUSPENSION -> suspension => rueda)

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 6;
	car.wheels = new Wheel[6];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);// (distancia en x del centro del coche, en z, en y)
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;
	
	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	// MIDDLE-LEFT ------------------------
	car.wheels[4].connection.Set(half_width - 0.3f * wheel_width, connection_height, 0);// (distancia en x del centro del coche, en z, en y)
	car.wheels[4].direction = direction;
	car.wheels[4].axis = axis;
	car.wheels[4].suspensionRestLength = suspensionRestLength;
	car.wheels[4].radius = wheel_radius;
	car.wheels[4].width = wheel_width;
	car.wheels[4].front = false;
	car.wheels[4].drive = false;
	car.wheels[4].brake = false;
	car.wheels[4].steering = false;

	// MIDDLE-RIGHT ------------------------
	car.wheels[5].connection.Set((half_width - 0.3f * wheel_width)*-1.0f, connection_height, 0);// (distancia en x del centro del coche, en z, en y)
	car.wheels[5].direction = direction;
	car.wheels[5].axis = axis;
	car.wheels[5].suspensionRestLength = suspensionRestLength;
	car.wheels[5].radius = wheel_radius;
	car.wheels[5].width = wheel_width;
	car.wheels[5].front = false;
	car.wheels[5].drive = false;
	car.wheels[5].brake = false;
	car.wheels[5].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 0, 0);
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}



