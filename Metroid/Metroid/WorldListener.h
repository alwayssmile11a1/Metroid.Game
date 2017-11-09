#pragma once
#include"WorldContactListener.h"
#include"Player.h"

class WorldListener: public WorldContactListener
{
public:
	WorldListener();
	~WorldListener();

	//Override OnContact of WorldContactListener
	void OnContact(Body* bodyA, Body *bodyB);

};

