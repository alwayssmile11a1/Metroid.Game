#include "WorldListener.h"



WorldListener::WorldListener()
{
}


WorldListener::~WorldListener()
{
}

void WorldListener::OnCollisionEnter(Body* bodyA, Body *bodyB)
{
	//Console::Log("OnCollisionEnter");
}

void WorldListener::OnSersorEnter(Body *bodyA, Body *bodyB)
{
	if (bodyA->categoryBits == FOOT_BIT && bodyB->categoryBits!=PLAYER_BIT)
	{
		Player*player = (Player *)(bodyA->GetExtra());
		if (player != NULL)
		{
			Console::Log("Grounded");
			player->OnGrounded();
		}
	}
}