#pragma once
#include"HanabiWorld.h"
#include"Player.h"
#include "Skree.h"
#include "Zoomer.h"

class WorldListener: public WorldContactListener
{
public:
	WorldListener();
	~WorldListener();


	//Override OnContact of WorldContactListener
	void OnCollisionEnter(Body* bodyA, Body *bodyB,const Vector2 &CollisionDirection) override;

	void OnCollisionExit(Body* bodyA, Body* bodyB) override;

	void virtual OnColliding(Body*bodyA, Body* BodyB) override;

	void OnSersorEnter(Body *bodyA, Body *bodyB) override;

	void  OnSensorExit(Body*bodyA, Body* bodyB) override;
};

