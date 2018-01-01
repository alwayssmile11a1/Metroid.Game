#include "WorldListener.h"



WorldListener::WorldListener()
{
	
}


WorldListener::~WorldListener()
{
}


void WorldListener::OnCollisionEnter(Body* bodyA, Body *bodyB, const Vector2 &CollisionDirection)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case RIO_BIT*PLAYER_BIT:
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)bodyA->GetExtra();
			player->OnHitEnemy(true);

			Rio* rio = (Rio*)bodyB->GetExtra();
			rio->OnHitPlayer();

		}
		else
		{
			if (bodyB->categoryBits == PLAYER_BIT)
			{
				Player* player = (Player*)bodyB->GetExtra();
				player->OnHitEnemy(true);

				Rio* rio = (Rio*)bodyA->GetExtra();
				rio->OnHitPlayer();
			}
		}
		break;

	case BULLET_BIT*RIO_BIT:
		if (bodyA->categoryBits == RIO_BIT)
		{
			Rio* rio = (Rio*)bodyA->GetExtra();
			rio->OnHitBullet();

		}
		else
		{
			if (bodyB->categoryBits == RIO_BIT)
			{
				Rio* rio = (Rio*)bodyB->GetExtra();
				rio->OnHitBullet();
			}
		}
		break;

	case RIO_BIT*PLATFORM_BIT:
		if (bodyA->categoryBits == RIO_BIT)
		{
			Rio* rio = (Rio*)bodyA->GetExtra();

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
		break;

	case PLAYER_BIT*ZOOMER_BIT:
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			Player* player = (Player*)bodyA->GetExtra();
			player->OnHitEnemy(true);

			Zoomer* zoomer = (Zoomer*)bodyB->GetExtra();
			zoomer->OnHitPlayer();

		}
		else
		{
			if (bodyB->categoryBits == PLAYER_BIT)
			{
				Player* player = (Player*)bodyB->GetExtra();
				player->OnHitEnemy(true);


				Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
				zoomer->OnHitPlayer();

			}
		}
		break;


	case ZOOMER_BIT*PLATFORM_BIT:
		if (bodyA->categoryBits == ZOOMER_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
			zoomer->SetCurCollisionDirection(CollisionDirection, 0);
		}
		break;

	case ZOOMER_BIT*BREAKABLEPLATFORM_BIT: 
		if (bodyA->categoryBits == ZOOMER_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
			zoomer->SetCurCollisionDirection(CollisionDirection, 1);
		}
		break;

	case BULLET_BIT*ZOOMER_BIT:
		if (bodyA->categoryBits == ZOOMER_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
			zoomer->OnHitBullet();
			Bullet* bullet = (Bullet*)bodyB->GetExtra();
			bullet->OnHitEnemy();
		}
		else
		{
			if (bodyB->categoryBits == ZOOMER_BIT)
			{
				Zoomer* zoomer = (Zoomer*)bodyB->GetExtra();
				zoomer->OnHitBullet();
				Bullet* bullet = (Bullet*)bodyA->GetExtra();
				bullet->OnHitEnemy();
			}
		}
		break;
	case BREAKABLEPLATFORM_BIT*BULLET_BIT:
	{
		if (bodyA->categoryBits == BULLET_BIT)
		{
			//Update breakableplatform
			BreakablePlatform* breakablePlatform = (BreakablePlatform*)bodyB->GetExtra();
			breakablePlatform->OnHitBullet();

			//Update Bullet
			Bullet* bullet = (Bullet*)bodyA->GetExtra();
			bullet->OnHitEnemy();

		}

		break;
	}
	case KRAID_BIT*BULLET_BIT:
	{
		if (bodyA->categoryBits == BULLET_BIT)
		{
			//Update Kraid
			Kraid* kraid = (Kraid*)bodyB->GetExtra();
			kraid->OnHitBullet();


			//Update Bullet
			Bullet* bullet = (Bullet*)bodyA->GetExtra();
			bullet->OnHitEnemy();

		}

		break;
	}
	case DOOR_BIT*BULLET_BIT:
	{
		if (bodyA->categoryBits == BULLET_BIT)
		{
			Door *door = (Door*)bodyB->GetExtra();
			if (bodyB->GetID() == "right")
			{
				Console::Log("Shoot right door\n");
				door->ROnhitBullet();
			}
			if (bodyB->GetID() == "left")
			{
				Console::Log("Shoot left door\n");
				door->LOnhitBullet();
			}
			

			//Update Bullet
			Bullet* bullet = (Bullet*)bodyA->GetExtra();
			bullet->OnHitEnemy();
			//bullet->IsDestroyed();
		}
		break;
	}
	case DOOR_BIT*PLAYER_BIT:
	{
		if (bodyA->categoryBits == PLAYER_BIT)
		{
			Console::Log("The player colliding with door\n");
			//Player *player = (Player*)bodyA->GetExtra();
			Door *door = (Door*)bodyB->GetExtra();
			if (bodyB->GetID() == "left" && door->IsROpen()==true)
			{
				door->SetLeftOpen(true);
				door->SetRightOpen(false);
				//door->SetCanPassRight(false);
				//door->SetCanPassLeft(true);
				//Console::Log("Can't pass right\n");
			}
			if (bodyB->GetID() == "right" && door->IsLOpen() == true)
			{
				door->SetLeftOpen(false);
				door->SetRightOpen(true);
				//door->SetCanPassRight(true);
				//door->SetCanPassLeft(false);
				//Console::Log("Can't pass left\n");
			}
			if (bodyB->GetID() == "mid")
			{
				bodyB->categoryBits = 0;
				if (door->IsROpen() == true)
				{
					door->SetCanPassLeft(true);
					Console::Log("You can pass left\n");
				}
				if (door->IsLOpen() == true)
				{
					door->SetCanPassRight(true);
					Console::Log("You can pass right\n");
				}
			}
		}
		break;
	}
	case HEALTHPILE_BIT*BULLET_BIT:
	{
		if (bodyA->categoryBits == BULLET_BIT)
		{
			//Update HealthPile
			HealthPile* healthPile = (HealthPile*)bodyB->GetExtra();
			healthPile->OnHitBullet();

			//Update Bullet
			Bullet* bullet = (Bullet*)bodyA->GetExtra();
			bullet->OnHitEnemy();

		}
		break;
	}
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
			zoomer->SetCurCollisionDirection(collisionDirection, 1);
		}
		break;

	case ZOOMER_BIT*BREAKABLEPLATFORM_BIT:
		if (bodyA->categoryBits == ZOOMER_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyA->GetExtra();
			zoomer->SetCurCollisionDirection(collisionDirection, 1);

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

	case PLAYER_BIT*SKREE_BIT:
	{
		if (bodyA->categoryBits == SKREE_BIT)
		{
			Player* player = (Player*)bodyB->GetExtra();
			if (bodyA->GetPosition().x > bodyB->GetPosition().x)
			{
				player->OnHitEnemy(true);
			}
			else
			{
				player->OnHitEnemy(false);
			}

		}
		break;
	}
	
	case PLATFORM_BIT*SKREE_BIT:
	{
		if (bodyA->categoryBits == SKREE_BIT)
		{
			Skree* skree = (Skree*)bodyA->GetExtra();
			skree->OnHitGround();
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
			healthItem->OnHitPlayer();

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
			skree->OnHitBullet();


			//Update Bullet
			Bullet* bullet = (Bullet*)bodyB->GetExtra();
			bullet->OnHitEnemy();

		}

		break;
	}
	case BULLET_BIT*RIPPER_BIT:
	{
		if (bodyA->categoryBits == RIPPER_BIT)
		{
			Ripper* ripper = (Ripper*)bodyA->GetExtra();
			ripper->OnHitBullet();


			//Update Bullet
			Bullet* bullet = (Bullet*)bodyB->GetExtra();
			bullet->OnHitEnemy();
		}

		break;
	}
	case BULLET_BIT*MOTHERBRAIN_BIT:
	{
		if (bodyA->categoryBits == MOTHERBRAIN_BIT)
		{
			//Update MotherBrain
			MotherBrain* motherBrain = (MotherBrain*)bodyA->GetExtra();
			motherBrain->OnHitBullet();


			//Update Bullet
			Bullet* bullet = (Bullet*)bodyB->GetExtra();
			bullet->OnHitEnemy();

		}

		break;
	}
	case CANNON_BIT*PLATFORM_BIT: //also equal MOTHERBRAIN_BIT*PLAYER_BIT
	{
		if (bodyA->categoryBits == CANNON_BIT)
		{
			//Update Cannon
			Cannon* cannon = (Cannon*)bodyA->GetExtra();
			cannon->OnHitGround();

		}
		else if (bodyA->categoryBits == MOTHERBRAIN_BIT) //Mother Brain
		{
			//Update Player
			Player* player = (Player*)bodyB->GetExtra();
			if (bodyA->GetPosition().x > bodyB->GetPosition().x)
			{
				player->OnHitEnemy(true);
			}
			else
			{
				player->OnHitEnemy(false);
			}
		}

		break;
	}	
	case CANNON_BIT*PLAYER_BIT:
	{
		if (bodyA->categoryBits == CANNON_BIT)
		{
			//Update Player
			Player* player = (Player*)bodyB->GetExtra();
			if (bodyA->GetPosition().x > bodyB->GetPosition().x)
			{
				player->OnHitEnemy(true);
			}
			else
			{
				player->OnHitEnemy(false);
			}

		}
		break;
	}
	case CIRCLECANNON_BIT*PLAYER_BIT://== RIPPER_BIT*PLATFORM_BIT
	{
		if (bodyA->categoryBits == CIRCLECANNON_BIT)
		{
			//Update Player
			Player* player = (Player*)bodyB->GetExtra();

			if (bodyA->GetPosition().x > bodyB->GetPosition().x)
			{
				player->OnHitEnemy(true);
			}
			else
			{
				player->OnHitEnemy(false);
			}

		}
		else if (bodyA->categoryBits == RIPPER_BIT)
		{
			Ripper* ripper = (Ripper*)bodyA->GetExtra();
			ripper->OnHitGround();

		}

		break;
	}
	case RIPPER_BIT*PLAYER_BIT:
	{
		if (bodyA->categoryBits == RIPPER_BIT)
		{
			//Console::Log("Ripper has collided with Player\n");
			Player* player = (Player*)bodyB->GetExtra();
			player->OnHitEnemy(true);

		}
		break;
	}

	case KRAID_BIT*PLAYER_BIT:
	{
		if (bodyA->categoryBits == KRAID_BIT)
		{
			//Update Player
			Player* player = (Player*)bodyB->GetExtra();

			if (bodyA->GetPosition().x > bodyB->GetPosition().x)
			{
				player->OnHitEnemy(true);
			}
			else
			{
				player->OnHitEnemy(false);
			}

			break;
		}
	}

	}
}

void WorldListener::OnSersorOverlaying(Body *bodyA, Body *bodyB)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case FOOT_BIT*PLATFORM_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player*player = (Player *)(bodyA->GetExtra());
			player->OnGrounded();
		}
		break;
	}
	case FOOT_BIT*BREAKABLEPLATFORM_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player*player = (Player *)(bodyA->GetExtra());
			player->OnGrounded();

		}
		break;
	}
	case HEAD_BIT*PLATFORM_BIT:
	{
		if (bodyA->categoryBits == HEAD_BIT)
		{
			Player*player = (Player *)(bodyA->GetExtra());

			player->OnHeadHit();
		}
		break;
	}
	case PLAYER_BIT*EXPLOSION_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
		{
			Player* player = (Player*)bodyB->GetExtra();
			if (bodyA->GetPosition().x > bodyB->GetPosition().x)
			{
				player->OnHitEnemy(true);
			}
			else
			{
				player->OnHitEnemy(false);
			}

		}

		break;
	}
	case SKREE_BIT*EXPLOSION_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
		{
			Skree* skree = (Skree*)bodyB->GetExtra();
			skree->OnHitBomb();

		}

		break;
	}
	case ZOOMER_BIT*EXPLOSION_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
		{
			Zoomer* zoomer = (Zoomer*)bodyB->GetExtra();
			zoomer->OnHitBomb();

		}

		break;
	}
	case BREAKABLEPLATFORM_BIT*EXPLOSION_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
		{
			BreakablePlatform* breakablePlatform = (BreakablePlatform*)bodyB->GetExtra();
			breakablePlatform->OnHitBomb();

		}

		break;
	}
	case EXPLOSION_BIT*MOTHERBRAIN_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
		{
			//Update MotherBrain
			MotherBrain* motherBrain = (MotherBrain*)bodyB->GetExtra();
			motherBrain->OnHitBomb();

		}

		break;
	}
	case HEALTHPILE_BIT*EXPLOSION_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
		{
			//Update HealthPile
			HealthPile* healthPile = (HealthPile*)bodyB->GetExtra();
			healthPile->OnHitBomb();

			break;
		}
	}
	case KRAID_BIT*EXPLOSION_BIT:
	{
		if (bodyA->categoryBits == EXPLOSION_BIT)
		{
			//Update HealthPile
			Kraid* kraid = (Kraid*)bodyB->GetExtra();
			kraid->OnHitBomb();

		}
		break;

	}
	}
}

void  WorldListener::OnSensorExit(Body*bodyA, Body* bodyB)
{
	switch (bodyA->categoryBits * bodyB->categoryBits)
	{
	case FOOT_BIT*PLATFORM_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player*player = (Player *)(bodyA->GetExtra());
			player->OnExitGround();
		}
		break;
	}
	case FOOT_BIT*BREAKABLEPLATFORM_BIT:
	{
		if (bodyA->categoryBits == FOOT_BIT)
		{
			Player*player = (Player *)(bodyA->GetExtra());
			player->OnExitGround();

		}
		break;
	}
	}
}