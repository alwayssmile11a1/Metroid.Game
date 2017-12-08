#pragma once
#include"HanabiWorld.h"
#include"Player.h"
#include "Skree.h"

class WorldListener: public WorldContactListener
{
public:
	WorldListener();
	~WorldListener();


	//Override OnContact of WorldContactListener
	void OnCollisionEnter(Body* bodyA, Body *bodyB) override;

	void OnSersorEnter(Body *bodyA, Body *bodyB) override;

};

