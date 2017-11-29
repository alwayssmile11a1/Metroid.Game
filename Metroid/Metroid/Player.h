#pragma once
#include "Object.h"
#include "World.h"
#include "TexturePacker.h"
#include "Animation.h" 
#include "Bullet.h"
#include <vector>

#define FIRERATE 0.1f

//Main character
class Player : public Object
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

	Body mainBody;
	Body foot;

	std::vector<Bullet*> bullets;

	World* world;
	
	//fire rate 
	float fireRate;
	float lastShot;


public:

	bool isJumping;
	bool isGrounded;
	bool isLookingup;
	bool isShooting;

public:
	Player();
	~Player();

	void Create(World *world);

	void HandleInput();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void Fire();

	void Release();

};

