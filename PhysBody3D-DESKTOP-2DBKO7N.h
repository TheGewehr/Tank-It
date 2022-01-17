#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "p2DynArray.h"
#include "glmath.h"

class btRigidBody;
class Module;

class btRigidBody;
class btCollisionShape;
struct btDefaultMotionState;
class Module;

class Sphere;
class Cube;
class Cylinder;
class Plane;

class Primitive;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D();
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	bool HasBody() const;
	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);

	void SetBodySphere(Sphere* primitive, float mass);


	void SetBodyCube(Cube* primitive, float mass);
	btRigidBody* body = nullptr;
private:
	
	void SetBody(btCollisionShape* shape, Primitive* parent, float mass);
	btCollisionShape* colShape;
	btDefaultMotionState* motionState;

public:
	Primitive* parentPrimitive;
	p2List<Module*> collision_listeners;
};

#endif // __PhysBody3D_H__