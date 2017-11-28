#pragma once
#include "Object.h"
#include "World.h"
#include "TexturePacker.h"
#include "Animation.h" 

//Main character
class Player : public Object
{
private:
	Texture characterTexture;

	Animation standingAnimation;
	Animation movingAnimation;
	Animation jumpingAnimation;
	Animation standAndShootupAnimation;
	Animation moveAndShootAnimation;
	Animation moveAndShootupAnimation;


	Body mainBody;
	Body foot;


public:

	bool isJumping;
	bool isGrounded;
	bool isLookingup;
	bool isShooting;

public:
	Player();
	~Player();

	void Create(World *world);

	void Update(float dt);

	void Release();

};

