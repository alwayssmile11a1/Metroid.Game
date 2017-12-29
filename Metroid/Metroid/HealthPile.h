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
	void Create(World *world, Texture *texture, int x, int y);

	void Create(World *world, Texture *texture, Body*body);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitBullet();

	void OnHitBomb();

	bool IsDead();

};
