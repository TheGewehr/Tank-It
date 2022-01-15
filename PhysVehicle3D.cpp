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
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) /* : PhysBody3D(body), vehicle(vehicle),*/ : info(info)
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
	for (int i = 0; i < info_w.num_wheels; ++i)
	{
		if (info_w.wheels[i].drive == true)
		{
			vehicle_t->applyEngineForce(force, i);
		}
	}
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

	
	btTransform trans;

	for (int i = 0; i < info_t.num_wheels; i++)
	{
		//trans = track[i].body->getWorldTransform();
		//trans.setOrigin(track[i].body->getCenterOfMassPosition());
		//track[i].body->setWorldTransform(trans);
		//track[i].body->get
		//track[i].parentPrimitive->SetRotation(30, vec3(1, 0, 0)); // Euler Angles
		//track[i].parentPrimitive->SetRotation(30, vec3(1, 0, 0)); // Euler Angles
		//track[i].parentPrimitive->SetRotation(30, vec3(1, 0, 0)); // Euler Angles
		
		//track[i].parentPrimitive->SetPos(track[i].body->getCenterOfMassPosition().x(), track[i].body->getCenterOfMassPosition().y(), track[i].body->getCenterOfMassPosition().z());
		
		//track[i].parentPrimitive->Render();

		
		
		//track[i].parentPrimitive->SetRotation(track[i].body->getAngularDamping(), vec3(track[i].body->getAngularFactor().x(), track[i].body->getAngularFactor().y(), track[i].body->getAngularFactor().z()));
		for (uint n = 0; n < count; n++) {

			trans = track[i].body->getWorldTransform();
			
			btQuaternion q = trans.getRotation();
			
			track[i].parentPrimitive->SetPos(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
			//track[i].SetTransform(trans.getRotation());
			
			
			//track[i].parentPrimitive->body.
			track[i].parentPrimitive->Render();
		}


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
	return float();
}