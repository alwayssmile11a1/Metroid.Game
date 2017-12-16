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
				Console::Log("Player hits zoomer\n");
				player->OnHitEnemy(true);
			}

			Zoomer* zoomer = (Zoomer*)bodyB->GetExtra();
			if (zoomer != NULL)
			{
				zoomer->OnHitPlayer();
				Console::Log("Zoomer hits player\n");
			}
		}
		else
		{
			if (bodyB->categoryBits == PLAYER_BIT)
			{
				Player* player = (Player*)bodyB->GetExtra();

				if (player != NULL)
				{
					Console::Log("Player hits zoomer\n");
					player->OnHitEnemy(true);
				}

				Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
				if (zoomer != NULL)
				{
					//zoomer->SetCurCollisionDirection(CollisionDirection, 2);
					zoomer->OnHitPlayer();
					Console::Log("Zoomer hits player\n");
				}
			}
		}
		break;


	case ZOOMER_BIT*PLATFORM_BIT:
		Console::Log("Zoomer hits platform\n");
		if (bodyA->categoryBits == ZOOMER_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
			if (zoomer != NULL)
			{
				zoomer->SetCurCollisionDirection(CollisionDirection, 0);
			}
		}
		break;

	case BULLET_BIT*ZOOMER_BIT:
		if (bodyA->categoryBits == ZOOMER_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
			if (zoomer != NULL)
			{
				zoomer->OnHitBullet();
				Console::Log("Buller hits zoomer\n");
			}
		}
		else
		{
			if (bodyB->categoryBits == ZOOMER_BIT)
			{
				Zoomer* zoomer = (Zoomer*)bodyB->GetExtra();
				if (zoomer != NULL)
				{
					zoomer->OnHitBullet();
					Console::Log("Buller hits zoomer\n");
				}
			}
		}
		break;


	case RIO_BIT*PLATFORM_BIT:
		if (bodyA->categoryBits == RIO_BIT)
		{
			Rio* rio = (Rio*)bodyA->GetExtra();
			if (rio != NULL)
			{
				if (CollisionDirection.y != NOT_COLLIDED && CollisionDirection.y < 0)
				{
					rio->OnHitRoof();
				}
				if (CollisionDirection.y != NOT_COLLIDED && CollisionDirection.y > 0)
				{
					rio->OnHitGround();
				}
				if (CollisionDirection.x != NOT_COLLIDED && CollisionDirection.x < 0)
				{
					rio->OnHitRight();
				}
				if (CollisionDirection.x != NOT_COLLIDED && CollisionDirection.x > 0)
				{
					rio->OnHitLeft();
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
			}
		}
		break;
	}
}


void WorldListener::OnCollisionExit(Body* bodyA, Body* bodyB, const Vector2 &collisionDirection)
{
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
	case FOOT_BIT*BREAKABLEPLATFORM_BIT:
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
	case PLAYER_BIT*EXPLOSION_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
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
	case SKREE_BIT*EXPLOSION_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
		{
			Skree* skree = (Skree*)bodyB->GetExtra();

			if (skree != NULL)
			{
				skree->OnHitBomb();
			}
		}

		break;
	}
	case ZOOMER_BIT*EXPLOSION_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyB->GetExtra();

			if (zoomer != NULL)
			{
				zoomer->OnHitBomb();
			}
		}

		break;
	}
	case BREAKABLEPLATFORM_BIT*EXPLOSION_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
		{
			BreakablePlatform* breakablePlatform = (BreakablePlatform*)bodyB->GetExtra();

			if (breakablePlatform != NULL)
			{
				breakablePlatform->OnHitBomb();
			}
		}

		break;
	}


	}
}

void  WorldListener::OnSensorExit(Body*bodyA, Body* bodyB)
{
	
}