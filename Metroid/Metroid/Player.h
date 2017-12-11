#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "Bullet.h"
#include <vector>
#include "CollisionBit.h"
#include "HanabiStateManager.h"

#define FIRERATE 0.1f
#define MAXJUMPTIME 0.3

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

	StateManager characterStateManager;

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

	void Release();

};

