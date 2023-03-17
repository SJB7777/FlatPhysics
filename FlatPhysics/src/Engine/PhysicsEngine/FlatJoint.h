#pragma once

#include "FlatBody.h"

namespace FlatPhysics {

	enum class JointType {
		Distance = 0,
		Spring = 1,
		Weld = 2,
		Rope = 3,
		DampingSpring
	};

	class FlatJoint {
	private:
		float damping = 10;
		FlatBody* bodyA;
		FlatBody* bodyB;
		JointType type;
		float distance;
		float magnitude;
	public:
		FlatJoint(FlatBody* a, FlatBody* b, JointType type, float distance, float magnitude, float damping = 300.0f) : 
			bodyA(a), bodyB(b), type(type), distance(distance), magnitude(magnitude), damping(damping){}

		void ApplyForce();

		void SetDistance(float d) { distance = d; }

		float GetDistance() const { return distance; }

		FlatBody* GetBodyA() const { return bodyA; }

		FlatBody* GetBodyB() const { return bodyB; }

		
	};

}
