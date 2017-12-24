#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"
#include "Player.h"

#define TURNINGDELAYTIME 1.5
#define KRAIDBULLETLIVETIME 2
#define KRAIDBOOMERANGLIVETIME 1

class KraidBullet: public Sprite
{
public:
	Body * body;
};



class Kraid : public Sprite
{

private:
	Animation animation;
	Body* body;


	int health;
	
	Player* player;

	float stateTime;
	
	float bulletStateTime;

	float boomerangStateTime;

	float lastShot;

	std::vector<KraidBullet> bullets;
	std::vector<KraidBullet> boomerangs;
	Animation boomerangAnimation;

public:
	Kraid();
	~Kraid();
	void Create(World *world, Texture *texture, Player*player, int x, int y);

	void HandlePhysics();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitBullet();

	void OnHitBomb();

	bool IsDead();

};

