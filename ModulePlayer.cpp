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
	TrackInfo track;
	TrackInfo try01;

	/////////////////////////////////////////////////////////////////////

	App->camera->Move(vec3(0.0f, 1.0f, 1.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	const int SnakeLength = 30;
	const float StartingSize = 0.3f;
	const float SizeIncrement = 0.2f;
	const float BallDistance = 0.3f;

	float XPos = 20.0f;
	float ZPos = 20.0f;
	float Size = StartingSize;

	size = { 0.5f, 0.1f, 0.5f };

	float section = SnakeLength * 0.25;

	float distanceNodeToNode = (size.x * 0.5) + 0.019f;
	PhysBody3D* aux = NULL;

	try01.chassis_size.Set(0, 0, 0);
	try01.chassis_offset.Set(0, 0.4, 0);
	try01.mass = 500.0f; // 500.0f
	try01.suspensionStiffness = 15.88f; // 15.88f  (fuerza de la suspension, fuerza de los springs de suspension)
	try01.suspensionCompression = 0.83f; // 0.83f (cuanto mas alto menos se comprime la suspension, limite de compresion)
	try01.suspensionDamping = 0.88f; // 0.88f (rigidez de la suspension)
	try01.maxSuspensionTravelCm = 20.0f;// 1000.0f (maxima distancia de movimiento de la suspension, maximo recorrido)
	try01.frictionSlip = 50.5; // 50.5 (friccion de las ruedas)
	try01.maxSuspensionForce = 6000.0f; // 6000.0f  (Maxima fuerza que puede ejercer la suspension)

	try01.wheels = new Track[SnakeLength];
	for (int n = 0; n < SnakeLength; n++)
	{
		//if (section > n)
		//{
		//	Cube* s = new Cube(size);
		//	s->SetPos(XPos + n, 10.f, ZPos);
		//	primitives.add(s);
		//	//s->SetPos(XPos + n, 10.f, ZPos);
		//	s->SetRotation(0, vec3(XPos, 1.f, ZPos));
		//
		//	XPos += StartingSize + BallDistance;
		//}
		//else if ((section * 2) > n && n >= section)
		//{
		//	Cube* s = new Cube(size);
		//	s->SetPos(XPos + n, 10.f, ZPos);
		//	primitives.add(s);
		//	//s->SetPos(XPos + n, 10.f, ZPos);
		//	s->SetRotation(90, vec3(XPos, 1.f, ZPos));
		//
		//	ZPos += StartingSize + BallDistance;
		//}
		//else if ((section * 3) > n && n >= section * 2)
		//{
		//	Cube* s = new Cube(size);
		//	s->SetPos(XPos + n, 10.f, ZPos);
		//	primitives.add(s);
		//	//s->SetPos(XPos + n, 10.f, ZPos);
		//	s->SetRotation(180, vec3(XPos, 1.f, ZPos));
		//
		//	XPos -= StartingSize + BallDistance;
		//}
		//else
		//{
		//	Cube* s = new Cube(size);
		//	s->SetPos(XPos + n, 10.f, ZPos);
		//	primitives.add(s);
		//	//s->SetPos(XPos + n, 10.f, ZPos);
		//	s->SetRotation(270, vec3(XPos, 1.f, ZPos));
		//
		//	ZPos -= StartingSize + BallDistance;
		//}
		/*



		Cube* s = new Cube(size);
		s->SetPos(3, 1.f + 0.5*cos(2*3.14f*n/ SnakeLength), 2 * sin(2 * 3.14f * n / SnakeLength));
		s->SetRotation(0, vec3(XPos, 1.f, ZPos));
		
		primitives.add(s);*/
		
		
		//XPos += StartingSize + BallDistance;
		try01.wheels[1].connection.Set(3, 1.f + 0.5 * cos(2 * 3.14f * n / SnakeLength), 2 * sin(2 * 3.14f * n / SnakeLength));// (distancia en x del centro del coche, en z, en y)
		try01.wheels[n].direction = (0, -1, 0);
		try01.wheels[n].axis = (-1, 0, 0);
		try01.wheels[n].radius = 1.0f;
		try01.wheels[n].width = 1.0f;
		
		


/*
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
		if (n == 0)
		{

		}
		else
		{
			App->physics->AddConstraintHinge(*aux, s->body,
				vec3(distanceNodeToNode, 0, 0), vec3(-distanceNodeToNode, 0, 0), vec3(0, 0, 1), vec3(0, 0, 1));
		}
	
		
		App->physics->AddBody(*s, 1);
		aux = &s->body;*/
	}
	

	//track01 = App->physics->AddVehicle(car);
	//vehicle->SetPos(5, 2, 2);
	/////////////////////////////////////////////////////////////////////
	// Try01 properties --------------------------------------
	
	

	
	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 2, 2);
	car.chassis_offset.Set(0, 0.4, 0);
	car.mass = 500.0f; // 500.0f
	car.suspensionStiffness = 15.88f; // 15.88f  (fuerza de la suspension, fuerza de los springs de suspension)
	car.suspensionCompression = 0.83f; // 0.83f (cuanto mas alto menos se comprime la suspension, limite de compresion)
	car.suspensionDamping = 0.88f; // 0.88f (rigidez de la suspension)
	car.maxSuspensionTravelCm = 20.0f;// 1000.0f (maxima distancia de movimiento de la suspension, maximo recorrido)
	car.frictionSlip = 50.5; // 50.5 (friccion de las ruedas)
	car.maxSuspensionForce = 6000.0f; // 6000.0f  (Maxima fuerza que puede ejercer la suspension)

	// Wheel properties ---------------------------------------
	float connection_height = 0.3f; // 1.6f (altura de las ruedas en la suspension)
	float wheel_radius = 0.1f; 
	float wheel_width = 0.6f;
	float suspensionRestLength = 1.0f; //1.2f (ESPACIO DE LA SUSPENSION -> suspension => rueda)
	float movementCoef = 0.3f;

	float wheel_radius_special = 0.3f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 18;

	//Wheel wel[10];
	//car.wheels =  wel;

	car.wheels = new Wheel[18];

	// la altura de las ruedas si que cambia, lo que no cambia el el print, que es el mismo para todas
	
	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width + wheel_width*0.5 + movementCoef, connection_height, half_length + wheel_radius);// (distancia en x del centro del coche, en z, en y)
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
	car.wheels[1].connection.Set(-half_width - wheel_width * 0.5 - movementCoef, connection_height, half_length + wheel_radius);
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
	car.wheels[2].connection.Set(half_width + wheel_width * 0.5 + movementCoef, connection_height, -half_length - wheel_radius);
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
	car.wheels[3].connection.Set(-half_width - wheel_width * 0.5 - movementCoef, connection_height, -half_length - wheel_radius);
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
	car.wheels[4].connection.Set(half_width + wheel_width * 0.5 + movementCoef, connection_height, 0);// (distancia en x del centro del coche, en z, en y)
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
	car.wheels[5].connection.Set(-half_width - wheel_width * 0.5 - movementCoef, connection_height, 0);// (distancia en x del centro del coche, en z, en y)
	car.wheels[5].direction = direction;
	car.wheels[5].axis = axis;
	car.wheels[5].suspensionRestLength = suspensionRestLength;
	car.wheels[5].radius = wheel_radius;
	car.wheels[5].width = wheel_width;
	car.wheels[5].front = false;
	car.wheels[5].drive = false;
	car.wheels[5].brake = false;
	car.wheels[5].steering = false;

	// ENGYNE FRONT LEFT ------------------------
	car.wheels[6].connection.Set(half_width + wheel_width * 0.5 + movementCoef, 1, half_length + 1);// (distancia en x del centro del coche, en z, en y)
	car.wheels[6].direction = direction;
	car.wheels[6].axis = axis;
	car.wheels[6].suspensionRestLength = suspensionRestLength;
	car.wheels[6].radius = wheel_radius*3;
	car.wheels[6].width = wheel_width;
	car.wheels[6].front = true;
	car.wheels[6].drive = true;
	car.wheels[6].brake = false;
	car.wheels[6].steering = false;

	// ENGYNE FRONT RIGHT ------------------------
	car.wheels[7].connection.Set(-half_width - wheel_width * 0.5 - movementCoef, 1, half_length + 1);// (distancia en x del centro del coche, en z, en y)
	car.wheels[7].direction = direction;
	car.wheels[7].axis = axis;
	car.wheels[7].suspensionRestLength = suspensionRestLength;
	car.wheels[7].radius = wheel_radius*3;
	car.wheels[7].width = wheel_width;
	car.wheels[7].front = true;
	car.wheels[7].drive = true;
	car.wheels[7].brake = false;
	car.wheels[7].steering = false;

	// ENGYNE BACK LEFT ------------------------
	car.wheels[8].connection.Set(half_width + wheel_width * 0.5 + movementCoef, 1, -half_length - 1);// (distancia en x del centro del coche, en z, en y)
	car.wheels[8].direction = direction;
	car.wheels[8].axis = axis;
	car.wheels[8].suspensionRestLength = suspensionRestLength;
	car.wheels[8].radius = wheel_radius * 3;
	car.wheels[8].width = wheel_width;
	car.wheels[8].front = true;
	car.wheels[8].drive = true;
	car.wheels[8].brake = false;
	car.wheels[8].steering = false;

	// ENGYNE BACK RIGHT ------------------------
	car.wheels[9].connection.Set(-half_width - wheel_width * 0.5 - movementCoef, 1,- half_length - 1);// (distancia en x del centro del coche, en z, en y)
	car.wheels[9].direction = direction;
	car.wheels[9].axis = axis;
	car.wheels[9].suspensionRestLength = suspensionRestLength;
	car.wheels[9].radius = wheel_radius * 3;
	car.wheels[9].width = wheel_width;
	car.wheels[9].front = true;
	car.wheels[9].drive = true;
	car.wheels[9].brake = false;
	car.wheels[9].steering = false;

	// ENGYNE AUXILIAR 01 FRONT LEFT ------------------------
	car.wheels[10].connection.Set(half_width + wheel_width  + movementCoef+  (wheel_width * 0.2f)*0.5, 1, half_length + 1);// (distancia en x del centro del coche, en z, en y)
	car.wheels[10].direction = direction;
	car.wheels[10].axis = axis;
	car.wheels[10].suspensionRestLength = suspensionRestLength;
	car.wheels[10].radius = wheel_radius * 4.f;
	car.wheels[10].width = wheel_width*0.2f;
	car.wheels[10].front = true;
	car.wheels[10].drive = false;
	car.wheels[10].brake = false;
	car.wheels[10].steering = false;

	// ENGYNE AUXILIAR 02 FRONT LEFT ------------------------
	car.wheels[11].connection.Set(half_width  + movementCoef - (wheel_width * 0.2f) * 0.5, 1, half_length + 1);// (distancia en x del centro del coche, en z, en y)
	car.wheels[11].direction = direction;
	car.wheels[11].axis = axis;
	car.wheels[11].suspensionRestLength = suspensionRestLength;
	car.wheels[11].radius = wheel_radius * 4.f;
	car.wheels[11].width = wheel_width * 0.2f;
	car.wheels[11].front = true;
	car.wheels[11].drive = false;
	car.wheels[11].brake = false;
	car.wheels[11].steering = false;

	// ENGYNE AUXILIAR 01 FRONT RIGHT ------------------------
	car.wheels[12].connection.Set(-half_width - wheel_width - movementCoef - (wheel_width * 0.2f) * 0.5, 1, half_length + 1);// (distancia en x del centro del coche, en z, en y)
	car.wheels[12].direction = direction;
	car.wheels[12].axis = axis;
	car.wheels[12].suspensionRestLength = suspensionRestLength;
	car.wheels[12].radius = wheel_radius * 4.f;
	car.wheels[12].width = wheel_width * 0.2f;
	car.wheels[12].front = true;
	car.wheels[12].drive = false;
	car.wheels[12].brake = false;
	car.wheels[12].steering = false;

	// ENGYNE AUXILIAR 02 FRONT RIGHT ------------------------
	car.wheels[13].connection.Set(-half_width  - movementCoef + (wheel_width * 0.2f) * 0.5, 1, half_length + 1);// (distancia en x del centro del coche, en z, en y)
	car.wheels[13].direction = direction;
	car.wheels[13].axis = axis;
	car.wheels[13].suspensionRestLength = suspensionRestLength;
	car.wheels[13].radius = wheel_radius * 4.f;
	car.wheels[13].width = wheel_width * 0.2f;
	car.wheels[13].front = true;
	car.wheels[13].drive = false;
	car.wheels[13].brake = false;
	car.wheels[13].steering = false;

	// ENGYNE AUXILIAR 01 BACK RIGHT ------------------------
	car.wheels[14].connection.Set(-half_width - wheel_width  - movementCoef - (wheel_width * 0.2f) * 0.5, 1, -half_length - 1); // (distancia en x del centro del coche, en z, en y)
	car.wheels[14].direction = direction;
	car.wheels[14].axis = axis;
	car.wheels[14].suspensionRestLength = suspensionRestLength;
	car.wheels[14].radius = wheel_radius * 4.f;
	car.wheels[14].width = wheel_width * 0.2f;
	car.wheels[14].front = true;
	car.wheels[14].drive = false;
	car.wheels[14].brake = false;
	car.wheels[14].steering = false;

	// ENGYNE AUXILIAR 02 BACK RIGHT ------------------------
	car.wheels[15].connection.Set(-half_width  - movementCoef + (wheel_width * 0.2f) * 0.5, 1, -half_length - 1); // (distancia en x del centro del coche, en z, en y)
	car.wheels[15].direction = direction;
	car.wheels[15].axis = axis;
	car.wheels[15].suspensionRestLength = suspensionRestLength;
	car.wheels[15].radius = wheel_radius * 4.f;
	car.wheels[15].width = wheel_width * 0.2f;
	car.wheels[15].front = true;
	car.wheels[15].drive = false;
	car.wheels[15].brake = false;
	car.wheels[15].steering = false;

	// ENGYNE AUXILIAR 01 BACK LEFT ------------------------
	car.wheels[16].connection.Set(half_width + wheel_width  + movementCoef + (wheel_width * 0.2f) * 0.5, 1, -half_length - 1); // (distancia en x del centro del coche, en z, en y)
	car.wheels[16].direction = direction;
	car.wheels[16].axis = axis;
	car.wheels[16].suspensionRestLength = suspensionRestLength;
	car.wheels[16].radius = wheel_radius * 4.f;
	car.wheels[16].width = wheel_width * 0.2f;
	car.wheels[16].front = true;
	car.wheels[16].drive = false;
	car.wheels[16].brake = false;
	car.wheels[16].steering = false;

	// ENGYNE AUXILIAR 02 BACK LEFT ------------------------
	car.wheels[17].connection.Set(half_width  + movementCoef - (wheel_width * 0.2f) * 0.5, 1, -half_length - 1); // (distancia en x del centro del coche, en z, en y)
	car.wheels[17].direction = direction;
	car.wheels[17].axis = axis;
	car.wheels[17].suspensionRestLength = suspensionRestLength;
	car.wheels[17].radius = wheel_radius * 4.f;
	car.wheels[17].width = wheel_width * 0.2f;
	car.wheels[17].front = true;
	car.wheels[17].drive = false;
	car.wheels[17].brake = false;
	car.wheels[17].steering = false;

	// TRACK INFO ------------------------------------
	track.mass = 1.0f;
	track.num_wheels = 19;
	track.wheels = new Track[track.num_wheels];
	
	// ---------------------------------------------------
	track.wheels[0].axis = axis;
	track.wheels[0].connection.Set(0, 0, 0);
	track.wheels[0].depth = 0.1f;
	track.wheels[0].height = 0.5f;
	track.wheels[0].width = 0.5f;

	// ---------------------------------------------------
	track.wheels[1].axis = axis;
	track.wheels[1].connection.Set(0, 0, 0);
	track.wheels[1].depth = 0.1f;
	track.wheels[1].height = 0.5f;
	track.wheels[1].width = 0.5f;

	// ---------------------------------------------------
	track.wheels[2].axis = axis;
	track.wheels[2].connection.Set(0, 0, 0);
	track.wheels[2].depth = 0.1f;
	track.wheels[2].height = 0.5f;
	track.wheels[2].width = 0.5f;

	// --------------------------------------------------
	track.wheels[3].axis = axis;
	track.wheels[3].connection.Set(0, 0, 0);
	track.wheels[3].depth = 0.1f;
	track.wheels[3].height = 0.5f;
	track.wheels[3].width = 0.5f;

	// --------------------------------------------------
	track.wheels[4].axis = axis;
	track.wheels[4].connection.Set(0, 0, 0);
	track.wheels[4].depth = 0.1f;
	track.wheels[4].height = 0.5f;
	track.wheels[4].width = 0.5f;

	// ---------------------------------------------------
	track.wheels[5].axis = axis;
	track.wheels[5].connection.Set(0, 0, 0);
	track.wheels[5].depth = 0.1f;
	track.wheels[5].height = 0.5f;
	track.wheels[5].width = 0.5f;

	// ---------------------------------------------------
	track.wheels[6].axis = axis;
	track.wheels[6].connection.Set(0, 0, 0);
	track.wheels[6].depth = 0.1f;
	track.wheels[6].height = 0.5f;
	track.wheels[6].width = 0.5f;

	// ---------------------------------------------------
	track.wheels[7].axis = axis;
	track.wheels[7].connection.Set(0, 0, 0);
	track.wheels[7].depth = 0.1f;
	track.wheels[7].height = 0.5f;
	track.wheels[7].width = 0.5f;

	// ---------------------------------------------------
	track.wheels[8].axis = axis;
	track.wheels[8].connection.Set(0, 0, 0);
	track.wheels[8].depth = 0.1f;
	track.wheels[8].height = 0.5f;
	track.wheels[8].width = 0.5f;
	
	// --------------------------------------------------
	track.wheels[9].axis = axis;
	track.wheels[9].connection.Set(0, 0, 0);
	track.wheels[9].depth = 0.1f;
	track.wheels[9].height = 0.5f;
	track.wheels[9].width = 0.5f;

	// ---------------------------------------------------
	track.wheels[10].axis = axis;
	track.wheels[10].connection.Set(0, 0, 0);
	track.wheels[10].depth = 0.1f;
	track.wheels[10].height = 0.5f;
	track.wheels[10].width = 0.5f;

	// ---------------------------------------------------
	track.wheels[11].axis = axis;
	track.wheels[11].connection.Set(0, 0, 0);
	track.wheels[11].depth = 0.1f;
	track.wheels[11].height = 0.5f;
	track.wheels[11].width = 0.5f;

	track.wheels[12].axis = axis;
	track.wheels[12].connection.Set(0, 0, 0);
	track.wheels[12].depth = 0.1f;
	track.wheels[12].height = 0.5f;
	track.wheels[12].width = 0.5f;

	track.wheels[13].axis = axis;
	track.wheels[13].connection.Set(0, 0, 0);
	track.wheels[13].depth = 0.1f;
	track.wheels[13].height = 0.5f;
	track.wheels[13].width = 0.5f;

	track.wheels[14].axis = axis;
	track.wheels[14].connection.Set(0, 0, 0);
	track.wheels[14].depth = 0.1f;
	track.wheels[14].height = 0.5f;
	track.wheels[14].width = 0.5f;

	track.wheels[15].axis = axis;
	track.wheels[15].connection.Set(0, 0, 0);
	track.wheels[15].depth = 0.1f;
	track.wheels[15].height = 0.5f;
	track.wheels[15].width = 0.5f;

	track.wheels[16].axis = axis;
	track.wheels[16].connection.Set(0, 0, 0);
	track.wheels[16].depth = 0.1f;
	track.wheels[16].height = 0.5f;
	track.wheels[16].width = 0.5f;

	track.wheels[17].axis = axis;
	track.wheels[17].connection.Set(0, 0, 0);
	track.wheels[17].depth = 0.1f;
	track.wheels[17].height = 0.5f;
	track.wheels[17].width = 0.5f;

	track.wheels[18].axis = axis;
	track.wheels[18].connection.Set(0, 0, 0);
	track.wheels[18].depth = 0.1f;
	track.wheels[18].height = 0.5f;
	track.wheels[18].width = 0.5f;
	vehicle = App->physics->AddVehicleTrack(car, track);
	


	// Hacer que spawnee la chain ya en circulo para que aterrice en el cauce
	

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


	for (int i = 0; i < primitives.count(); i++)
	{
		Primitive* dummy;
		
		primitives.at(i, dummy);
		dummy->body.GetTransform(&dummy->transform);
		dummy->Render();
	}


	
	return UPDATE_CONTINUE;
}





