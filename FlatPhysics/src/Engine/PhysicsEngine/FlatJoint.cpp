#include "FlatJoint.h"

namespace FlatPhysics
{
	void FlatJoint::ApplyForce() {
        

        switch (type)
        {
        case JointType::Distance: 
        {
            FlatVector delta = bodyB->GetPosition() - bodyA->GetPosition();
            float deltaLength = FlatMath::Length(delta);
            float difference = deltaLength - distance;
            if (difference > 0.0f) {
                float forceMagnitude = difference * magnitude;
                FlatVector force = FlatMath::Normalize(delta) * forceMagnitude;
                bodyA->AddForce(force);
                bodyB->AddForce(-force);
            }
            break;
        }
        case JointType::Spring: 
        {
            FlatVector delta = bodyB->GetPosition() - bodyA->GetPosition();
            float deltaLength = FlatMath::Length(delta);
            float difference = deltaLength - distance;
            if (difference != 0) {
                float forceMagnitude = difference * magnitude;
                FlatVector force = FlatMath::Normalize(delta) * forceMagnitude;

                float massA = bodyA->Mass;
                float massB = bodyB->Mass;

                float totalMass = massA + massB;
                float ratioA = massA / totalMass;
                float ratioB = massB / totalMass;

                bodyA->AddForce(force * ratioA);
                bodyB->AddForce(-force * ratioB);
            }
            break;
        }
        case JointType::Weld: 
        {   
            FlatVector delta = bodyB->GetPosition() - bodyA->GetPosition();
            
            bodyA->MoveTo(bodyB->GetPosition() + distance * FlatMath::Normalize(delta));
            
            break;
        }
        case JointType::Rope:
        {
            FlatVector delta = bodyB->GetPosition() - bodyA->GetPosition();
            float deltaLength = FlatMath::Length(delta);
            if (deltaLength > distance) {
                float forceMagnitude = (deltaLength - distance) * magnitude;
                FlatVector force = FlatMath::Normalize(delta) * forceMagnitude;

                float massA = bodyA->Mass;
                float massB = bodyB->Mass;

                float totalMass = massA + massB;
                float ratioA = massA / totalMass;
                float ratioB = massB / totalMass;

                bodyA->AddForce(force * ratioA);
                bodyB->AddForce(-force * ratioB);
            }
            break;
        }
        case JointType::DampingSpring:
        {
            FlatVector delta = bodyB->GetPosition() - bodyA->GetPosition();
            float deltaLength = FlatMath::Length(delta);
            float difference = deltaLength - distance;
            if (difference != 0) {
                float forceMagnitude = difference * magnitude;

                // calculate relative velocity between the two bodies
                FlatVector relativeVelocity = bodyB->LinearVelocity - bodyA->LinearVelocity;
                
                // calculate damping force based on relative velocity
                float dampingForceMagnitude = damping * FlatMath::Dot(relativeVelocity, FlatMath::Normalize(delta));
                FlatVector dampingForce = FlatMath::Normalize(delta) * dampingForceMagnitude;

                // calculate total force acting on each body
                FlatVector totalForce = FlatMath::Normalize(delta) * (forceMagnitude + dampingForceMagnitude);
                float massA = bodyA->Mass;
                float massB = bodyB->Mass;
                float totalMass = massA + massB;
                float ratioA = massA / totalMass;
                float ratioB = massB / totalMass;

                // apply forces to each body
                bodyA->AddForce(totalForce * ratioA);
                bodyB->AddForce(-totalForce * ratioB);
            }
            break;
        }
        default:
            break;
        }
	}
	
}