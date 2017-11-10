#pragma once
#include "Object.h"
#include "World.h"
#include "TexturePacker.h"
#include "Animation.h" 

//Main character
class Player : public Object
{
private:
	Texture* characterTexture;

	Animation standingAnimation;
	Animation movingAnimation;

public:
	Body* foot;
	bool isJumping;
	bool isGrounded;

public:
	Player();
	~Player();

	void Create(World &world);

	void HandleInput(float dt);

	void Release();

};

