#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "ModulePlayer.h"
#include "Bullet/include/btBulletDynamicsCommon.h"
#include "Application.h"
#include <cmath>
// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), /*vehicle(vehicle), */ info(info)
{

}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	//delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render_v()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < info.num_wheels; ++i)
	{
		wheel.radius = info.wheels[i].radius;
		wheel.height = info.wheels[i].width;
	
		//vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);
	
		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);

	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();


	chassis.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce_v(float force)
{
	for(int i = 0; i < info.num_wheels; ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake_v(float force)
{
	for(int i = 0; i < info.num_wheels; ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn_v(float degrees)
{
	for(int i = 0; i < info.num_wheels; ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh_v() const
{
	return vehicle->getCurrentSpeedKmHour();
}

// ----------------------------------------------------------------------------
TrackInfo::~TrackInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysTrack3D::PhysTrack3D(btRigidBody* body_c, btRaycastVehicle* vehicle, const VehicleInfo& info_wh, const TrackInfo& info_t, int trackCount, PhysBody3D* track_t) : PhysVehicle3D(body_c, vehicle, info_wh), vehicle_t(vehicle),info_w(info_wh), info_t(info_t), count(trackCount), track(track_t)
{

	for (int i = 0; i < trackCount; i++)
	{
		App->player->primitives.add(track[i].parentPrimitive);
		
	}
}

// ----------------------------------------------------------------------------
PhysTrack3D::~PhysTrack3D()
{
	
	delete vehicle_t;
}

void PhysTrack3D::ApplyEngineForce(float force)
{
	btTransform trans = vehicle_t->getChassisWorldTransform();
		
	
	float N = force * 500 * 9.8; // Mass * grav

	float drag = N * 0.00005 ; // N * nu
	
	
	// seno del angulo por total drag = drag
	// cos del angulo por tota drag = lift

	
	for (int i = 0; i < info_w.num_wheels; ++i)
	{
		if (info_w.wheels[i].drive == true)
		{
			
			vehicle_t->applyEngineForce(force - drag, i);
		}
	}
	
	// DRAG FUIM
	float vel = GetKmh();
	btTransform a = vehicle_t->getChassisWorldTransform();
	body->applyForce(btVector3(0, vel * 0.005, 0), a.getOrigin());

}

// ----------------------------------------------------------------------------
void PhysTrack3D::Brake(float force)
{
	for (int i = 0; i < info_w.num_wheels; ++i)
	{
		if (info_w.wheels[i].brake == true)
		{
			vehicle_t->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysTrack3D::Turn(float degrees)
{
	for (int i = 0; i < info_w.num_wheels; ++i)
	{
		if (info_w.wheels[i].steering == true)
		{
			vehicle_t->setSteeringValue(degrees, i);
		}
	}
}



// ----------------------------------------------------------------------------
void PhysTrack3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for (int i = 0; i < info_w.num_wheels; ++i)
	{
		wheel.radius = info_w.wheels[i].radius;
		wheel.height = info_w.wheels[i].width;
	
		//vehicle->updateWheelTransform(i);
		vehicle_t->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);
	
		wheel.Render();
	}
	
		
	for (uint n = 0; n < count; n++) 
	{

		track[n].GetTransform(&track[n].parentPrimitive->transform);

		track[n].parentPrimitive->Render();
	}


	


	Cube chassis(info_w.chassis_size.x, info_w.chassis_size.y, info_w.chassis_size.z);
	vehicle_t->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle_t->getChassisWorldTransform().getRotation();
	btVector3 offset(info_w.chassis_offset.x, info_w.chassis_offset.y, info_w.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();


	chassis.Render();
}


// ----------------------------------------------------------------------------
float PhysTrack3D::GetKmh() const
{
	return vehicle_t->getCurrentSpeedKmHour();
}

vec3 PhysVehicle3D::GetForwardVector() const
{
	btVector3 f_vector = vehicle->getForwardVector();
	return vec3(f_vector.getX(), f_vector.getY(), f_vector.getZ());
}

vec3 PhysVehicle3D::GetUpperVector() const
{
	btVector3 u_vector = vehicle->getUpVector();
	return vec3(u_vector.getX(), u_vector.getY(), u_vector.getZ());
}

vec3 PhysTrack3D::GetForwardVector() const
{
	btVector3 f_vector = vehicle_t->getForwardVector();
	return vec3(f_vector.getX(), f_vector.getY(), f_vector.getZ());
}

vec3 PhysTrack3D::GetUpperVector() const
{
	btVector3 u_vector = vehicle->getUpVector();
	return vec3(u_vector.getX(), u_vector.getY(), u_vector.getZ());
}