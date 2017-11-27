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
	Body* foot;

public:

	bool isJumping;
	bool isGrounded;

public:
	Player();
	~Player();

	void Create(World &world);

	void Update(float dt);

	void Release();

};

