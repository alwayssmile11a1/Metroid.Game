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
	case PLAYER_BIT*ZOOMER_BIT:
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)bodyA->GetExtra();

			if (player != NULL)
			{
				player->OnHitEnemy(true);
			}

		}
		break;


	case ZOOMER_BIT*PLATFORM_BIT:
		if (bodyA->categoryBits == ZOOMER_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
			if (zoomer != NULL)
			{
				zoomer->SetCurCollisionDirection(CollisionDirection, 0);
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
					zoomer->SetCurCollisionDirection(CollisionDirection, 0);
					//zoomer->curCollisionDirection.x = CollisionDirection.x;
					//zoomer->curCollisionDirection.y = CollisionDirection.y;
				}
			}
		}
		break;

	}
	



}

void  WorldListener::OnColliding(Body* bodyA, Body* bodyB, const Vector2 &collisionDirection)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case ZOOMER_BIT*PLATFORM_BIT:
		if (bodyA->categoryBits == ZOOMER_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
			if (zoomer != NULL)
			{
				zoomer->SetCurCollisionDirection(collisionDirection, 1);
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
					zoomer->SetCurCollisionDirection(collisionDirection, 1);
					//zoomer->curCollisionDirection.x = CollisionDirection.x;
					//zoomer->curCollisionDirection.y = CollisionDirection.y;
				}
			}
		}
		break;
	}
}


void WorldListener::OnCollisionExit(Body* bodyA, Body* bodyB, const Vector2 &collisionDirection)
{
	//Console::Log("End Collide");
	//switch (bodyA->categoryBits * bodyB->categoryBits)
	//{
	//case ZOOMER_BIT*PLATFORM_BIT:
	//	if (bodyA->categoryBits == ZOOMER_BIT)
	//	{
	//		Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
	//		if (zoomer != NULL)
	//		{
	//			zoomer->SetCurCollisionDirection(collisionDirection);
	//			//zoomer->curCollisionDirection.x = CollisionDirection.x;
	//			//zoomer->curCollisionDirection.y = CollisionDirection.y;
	//		}
	//	}
	//	else
	//	{
	//		if (bodyB->categoryBits == ZOOMER_BIT)
	//		{
	//			Zoomer* zoomer = (Zoomer*)bodyB->GetExtra();
	//			if (zoomer != NULL)
	//			{
	//				zoomer->SetCurCollisionDirection(collisionDirection);
	//				//zoomer->curCollisionDirection.x = CollisionDirection.x;
	//				//zoomer->curCollisionDirection.y = CollisionDirection.y;
	//			}
	//		}
	//	}
	//	break;
	//}
}


void WorldListener::OnSersorEnter(Body *bodyA, Body *bodyB)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case FOOT_BIT*PLATFORM_BIT:
	{
		Player*player = (Player *)(bodyA->GetExtra());
		if (player != NULL)
		{
			player->OnGrounded();
		}
		break;
	}

	case PLAYER_BIT*SKREE_BIT:
	{
		if (bodyA->categoryBits == SKREE_BIT)
		{
			Player* player = (Player*)bodyB->GetExtra();

			if (player != NULL)
			{
				if (bodyA->GetPosition().x > bodyB->GetPosition().x)
				{
					player->OnHitEnemy(true);
				}
				else
				{
					player->OnHitEnemy(false);
				}
			}

		}
		break;
	}
	case PLATFORM_BIT*SKREE_BIT:
	{
		if (bodyA->categoryBits == SKREE_BIT)
		{
			Skree* skree = (Skree*)bodyA->GetExtra();

			if (skree != NULL)
			{
				skree->OnHitGround();
			}

		}
		break;
	}
	case PLAYER_BIT*MARUMARIITEM_BIT:
	{
		if (bodyA->categoryBits == MARUMARIITEM_BIT)
		{
			Player* player = (Player*)bodyB->GetExtra();
			player->OnHitRollItem();

			MaruMariItem* item = (MaruMariItem*)bodyA->GetExtra();
			item->OnHitPlayer();
		}
		break;
	}

	case PLAYER_BIT*BOMBITEM_BIT:
	{
		if (bodyA->categoryBits == BOMBITEM_BIT)
		{
			Player* player = (Player*)bodyB->GetExtra();
			player->OnHitBombItem();

			BombItem* item = (BombItem*)bodyA->GetExtra();
			item->OnHitPlayer();
		}
		break;
	}

	case PLAYER_BIT*HEALTHITEM_BIT:
	{
		if (bodyA->categoryBits == HEALTHITEM_BIT)
		{
			HealthItem* healthItem = (HealthItem*)bodyA->GetExtra();

			if (healthItem != NULL)
			{
				healthItem->OnHitPlayer();
			}

			Player* player = (Player*)bodyB->GetExtra();
			player->OnHitHealthItem();
		}

		break;
	}

	case BULLET_BIT*SKREE_BIT:
	{
		if (bodyA->categoryBits == SKREE_BIT)
		{
			//Update skree
			Skree* skree = (Skree*)bodyA->GetExtra();
			if (skree != NULL)
			{
				skree->OnHitBullet();
			}

			//Update Bullet
			Bullet* bullet = (Bullet*)bodyB->GetExtra();
			if (bullet != NULL)
			{
				bullet->OnHitEnemy();
			}
		}
		
		break;
	}

	}
}

void WorldListener::OnSersorOverlaying(Body *bodyA, Body *bodyB)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case HEAD_BIT*PLATFORM_BIT:
	{
		Player*player = (Player *)(bodyA->GetExtra());
		if (player != NULL)
		{
			player->OnHeadHit();
		}
		break;
	}
	}
}

void  WorldListener::OnSensorExit(Body*bodyA, Body* bodyB)
{
	
}