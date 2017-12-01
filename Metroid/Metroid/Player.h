#pragma once
#include "World.h"
#include "TexturePacker.h"
#include "Animation.h" 
#include "Bullet.h"
#include <vector>
#include "CollisionBit.h"

#define FIRERATE 0.1f
#define MAXJUMPTIME 0.3

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
public:


public:
	Player();
	~Player();

	void Create(World *world);

	void HandleInput();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void Fire();

	void OnGrounded();

	void Release();

};

