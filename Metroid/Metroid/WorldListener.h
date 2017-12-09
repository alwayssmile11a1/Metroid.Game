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
	void OnCollisionEnter(Body* bodyA, Body *bodyB, Vector2 CollisionDirection) override;

	void OnSersorEnter(Body *bodyA, Body *bodyB) override;

};

