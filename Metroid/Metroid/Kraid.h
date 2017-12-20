#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"
#include "Player.h"

#define TURNINGDELAYTIME 1

class Kraid : public Sprite
{

private:
	Animation animation;
	Body* body;


	int health;
	
	Player* player;

	float stateTime;



public:
	Kraid();
	~Kraid();
	void Create(World *world, Texture *texture, Player*player, int x, int y);

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitBullet();

	void OnHitBomb();

	bool IsDead();

};

