#pragma once
#include "EnemySpecs.h"
#include "Game/Components/RigidBody.h"
#include "Game/Components/Transform.h"
#include "Game/Components/Combat.h"

class Enemy
{
public:
	struct Specs
	{
		Combat combat;
		std::string modelPath;
		float fov;
		float viewDist;
		float speed;
		
		Specs(Combat combat, const std::string& modelPath, float fov, float viewDist, float speed);

	};

protected:
	static Specs defualtSpecs;

	RigidBody rigidbody;
	Transform transform;
	Specs activeSpecs;
	
public:
	Enemy(const Transform& transform);

	bool PlayerInBound() const;
	virtual void Update(float dt);

	Transform& GetTransform() { return transform; }
	RigidBody& GetRigidBody() { return rigidbody; }
	Specs& GetSpecs() { return activeSpecs; }

	const glm::mat4 &GetM() const;
};

