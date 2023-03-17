#pragma once
#include <vector>
#include <algorithm>
#include "FlatVector.h"
#include "Collisions.h"
#include "FlatManifold.h"
#include "FlatJoint.h"


namespace FlatPhysics {
	
	static int MinIterations() { return 1; }
	static int MaxIterations() { return 128; }


	class FlatWorld {

	private:

		
		std::vector<FlatJoint*> jointVector;
		std::vector<FlatBody*> bodyVector;
		FlatVector gravity;
		std::vector<std::pair<int, int>> contactPairs;

		FlatVector contactArray[2];
		FlatVector impulseArray[2];
		FlatVector raArray[2];
		FlatVector rbArray[2];
		FlatVector frictionImpulseArray[2];
		float jArray[2];
	public:
		FlatWorld(const FlatVector& gravity);
		~FlatWorld();

		int BodyCount();

		void AddBody(FlatBody* body);
		
		void RemoveBody(FlatBody* body);

		void RemoveJoint(FlatBody* body);

		void RemoveJoint(FlatJoint* joint);

		bool GetBody(int index, FlatBody* &body);

		void ConnectTwoBody(FlatBody* bodyA, FlatBody* bodyB, JointType type, float distance, float magnitude);

		void Step(float time, int iterations);
		void TestStep(float time, int iterations);
	private:
		void BroadPhase();
		void NarrowPhase();
		void StepBodies(float time, int totalIterations);

		void SeperateBodies(FlatBody* bodyA, FlatBody* bodyB, const FlatVector& mtv);
	public:
		void ResolveCollisionBasic(const FlatManifold& contact);

		void ResolveCollisionWithRotation(const FlatManifold& contact);

		void ResolveCollisionWithRotationAndFriction(const FlatManifold& contact);
	};
}
