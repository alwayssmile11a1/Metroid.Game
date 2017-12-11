#include "WorldListener.h"



WorldListener::WorldListener()
{
	
}


WorldListener::~WorldListener()
{
}


void WorldListener::OnCollisionEnter(Body* bodyA, Body *bodyB,const Vector2 &CollisionDirection)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case PLAYER_BIT*SKREE_BIT:
		if (bodyA->categoryBits == SKREE_BIT)
		{
			Skree* skree = (Skree*)bodyA->GetExtra();

			if (skree != NULL)
			{
				skree->OnHitPlayer();
			}

		}
		else
		{
			if (bodyB->categoryBits == SKREE_BIT)
			{
				Skree* skree = (Skree*)bodyB->GetExtra();

				if (skree != NULL)
				{
					skree->OnHitPlayer();
				}

			}
		}
		break;

	case PLATFORM_BIT*SKREE_BIT:
		if (bodyA->categoryBits == SKREE_BIT)
		{
			Skree* skree = (Skree*)bodyA->GetExtra();

			if (skree != NULL)
			{
				skree->OnHitGround();
			}

		}
		else
		{
			if (bodyB->categoryBits == SKREE_BIT)
			{
				Skree* skree = (Skree*)bodyB->GetExtra();

				if (skree != NULL)
				{
					skree->OnHitGround();
				}

			}
		}
		break;

	case ZOOMER_BIT*PLATFORM_BIT:
		if (bodyA->categoryBits == ZOOMER_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
			if (zoomer != NULL)
			{
				zoomer->SetCurCollisionDirection(CollisionDirection);
				//zoomer->curCollisionDirection.x = CollisionDirection.x;
				//zoomer->curCollisionDirection.y = CollisionDirection.y;
			}
		}
		else
		{
			if (bodyB->categoryBits == ZOOMER_BIT)
			{
				Zoomer* zoomer = (Zoomer*)bodyB->GetExtra();
				if (zoomer != NULL)
				{
					zoomer->SetCurCollisionDirection(CollisionDirection);
					//zoomer->curCollisionDirection.x = CollisionDirection.x;
					//zoomer->curCollisionDirection.y = CollisionDirection.y;
				}
			}
		}
		break;


	}
	



}

void  WorldListener::OnColliding(Body*bodyA, Body* BodyB)
{
	
}


void WorldListener::OnCollisionExit(Body* bodyA, Body* bodyB,const Vector2 &collisionDirection)
{
	//Console::Log("End Collide");
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case ZOOMER_BIT*PLATFORM_BIT:
		if (bodyA->categoryBits == ZOOMER_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
			if (zoomer != NULL)
			{
				zoomer->SetCurCollisionDirection(collisionDirection);
				//zoomer->curCollisionDirection.x = CollisionDirection.x;
				//zoomer->curCollisionDirection.y = CollisionDirection.y;
			}
		}
		else
		{
			if (bodyB->categoryBits == ZOOMER_BIT)
			{
				Zoomer* zoomer = (Zoomer*)bodyB->GetExtra();
				if (zoomer != NULL)
				{
					zoomer->SetCurCollisionDirection(collisionDirection);
					//zoomer->curCollisionDirection.x = CollisionDirection.x;
					//zoomer->curCollisionDirection.y = CollisionDirection.y;
				}
			}
		}
		break;
	}
}


void WorldListener::OnSersorEnter(Body *bodyA, Body *bodyB)
{
	if (bodyA->categoryBits == FOOT_BIT)
	{
		Player*player = (Player *)(bodyA->GetExtra());
		if (player != NULL)
		{
			player->OnGrounded();
		}
	}
}

void  WorldListener::OnSensorExit(Body*bodyA, Body* bodyB)
{
	
}