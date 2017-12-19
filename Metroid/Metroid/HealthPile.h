#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"



class HealthPile : public Sprite
{

private:
	std::vector<TextureRegion> regions;
	Body* body;


	int health;
	World *world;

public:
	HealthPile();
	~HealthPile();
	void Create(World *world, Texture *skreeTexture, int x, int y);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitBullet();

	void OnHitBomb();

	bool IsDead();

};
