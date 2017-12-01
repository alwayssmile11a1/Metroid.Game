#pragma once
#include "World.h"
#include "Animation.h"
#include "TexturePacker.h"

#define SKREE_BIT 16

class Skree:public Sprite
{
private:
	Animation movingAnimation;
	Body* body;

public:
	Skree();
	~Skree();
	Skree(World *world, Texture *texture);

	void HandleInput();

	void Render(SpriteBatch *batch);

	void Update(float dt);

};

