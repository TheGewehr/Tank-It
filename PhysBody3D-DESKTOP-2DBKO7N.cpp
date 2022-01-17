#include "PhysBody3D.h"
#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "glmath.h"
#include "ModulePhysics3D.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

PhysBody3D::PhysBody3D()
{
	parentPrimitive = NULL;
	colShape = NULL;
}

// =================================================
PhysBody3D::PhysBody3D(btRigidBody* body) : body(body)
{

}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{
	if (HasBody() == true)
	{
		// there might be an error here
		delete body;
		delete colShape;
		delete motionState;
	}

	delete body;
}

bool PhysBody3D::HasBody() const
{
	return body != nullptr;
}
// ---------------------------------------------------------
void PhysBody3D::Push(float x, float y, float z)
{
	if (HasBody())
	{
		body->activate();
		body->applyCentralForce(btVector3(x, y, z));
	}
}

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		body->getWorldTransform().getOpenGLMatrix(matrix);
	}
	
}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if (HasBody() == false)
		return;

	btTransform trans;
	trans.setFromOpenGLMatrix(matrix);
	body->setWorldTransform(trans);
	body->activate();
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	if (HasBody() == false)
		return;

	btTransform trans = body->getWorldTransform();
	trans.setOrigin(btVector3(x, y, z));
	body->setWorldTransform(trans);
	body->activate();
}

void PhysBody3D::SetBodySphere(Sphere* primitive, float mass)
{
	//SetBody(new btSphereShape(primitive->GetRadius()),
	//	primitive, mass);
}

void PhysBody3D::SetBodyCube(Cube* primitive, float mass)
{
	SetBody(new btBoxShape(btVector3(primitive->GetSize().x * 0.5, primitive->GetSize().y * 0.5, primitive->GetSize().z * 0.5)),
		primitive, mass);
}

void PhysBody3D::SetBody(btCollisionShape* shape, Primitive* parent, float mass)
{
	//assert(HasBody() == false);

	parentPrimitive = parent;

	colShape = shape;

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&parent->transform);

	btVector3 localInertia(0, 0, 0);
	if (mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	motionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);

	body = new btRigidBody(rbInfo);

	body->setUserPointer(this);
	if (body != NULL) App->physics->AddBodyToWorld(body);
	
}