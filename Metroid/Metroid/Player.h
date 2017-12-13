#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "Bullet.h"
#include <vector>
#include "CollisionBit.h"
#include "HanabiStateManager.h"

#define FIRERATE 0.1
#define MAXJUMPTIME 0.5
#define UNTOUCHABLETIME 0.3 

#include "HanabiSound.h"

//Main character
class Player : public Sprite
{
private:
	Texture characterTexture;
	Texture bulletTexture;

	Animation standingAnimation;
	Animation movingAnimation;
	Animation jumpingAnimation;
	Animation standAndShootupAnimation;
	Animation moveAndShootAnimation;
	Animation moveAndShootupAnimation;
	Animation jumpAndShootupAnimation;
	Animation jumpAndShootAnimation;
	Animation rollingAnimation;
	Animation jumpAndRollAnimation;
	StateManager characterStateManager;

	Body* mainBody;
	Body* foot;

	std::vector<Bullet*> bullets;

	World* world;
	
	//
	float lastShot;

	float jumpTime;

	bool isGrounded;
	bool isLookingup;
	bool isShooting;
	bool isRolling;
	bool canRoll;
	int health;

public:


public:
	Player();
	~Player();

	void Create(World *world, float x, float y);

	void HandleInput();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void Fire();

	void OnGrounded();

	void OnHitRollItem();

	void OnHitHealthItem();

	void OnHitEnemy();

	int GetHealth();

	void Release();

	
};

