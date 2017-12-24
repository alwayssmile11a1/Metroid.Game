#pragma once
#include"HanabiWorld.h"
#include"Player.h"
#include "Skree.h"
#include "Zoomer.h"
#include "Ripper.h"
#include "MaruMariItem.h"
#include "HealthItem.h"
#include "BombItem.h"
#include "BreakablePlatform.h"
#include "Rio.h"
#include "HanabiConsole.h"
#include "MotherBrain.h"
#include "Cannon.h"
#include "HealthPile.h"
#include "CircleCannon.h"
#include "Kraid.h"

class WorldListener: public WorldContactListener
{
public:
	WorldListener();
	~WorldListener();


	//Override OnContact of WorldContactListener
	void OnCollisionEnter(Body* bodyA, Body *bodyB, const Vector2 &CollisionDirection) override;

	void OnCollisionExit(Body* bodyA, Body* bodyB, const Vector2 &collisionDirection) override;

	void OnColliding(Body* bodyA, Body* BodyB, const Vector2 &collisionDirection) override;

	void OnSersorEnter(Body *bodyA, Body *bodyB) override;

	void OnSersorOverlaying(Body *bodyA, Body *bodyB) override;

	void  OnSensorExit(Body*bodyA, Body* bodyB) override;
};

