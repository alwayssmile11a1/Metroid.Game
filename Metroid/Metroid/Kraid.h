#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "CollisionBit.h"
#include "Player.h"

#define TURNINGDELAYTIME 1.5
#define KRAIDBULLETLIVETIME 1.5
#define KRAIDBOOMERANGLIVETIME 1
#define MAXHITBULLETTIME 0.2

class KraidBullet: public Sprite
{
public:
	Body * body;
};



class Kraid : public Sprite
{

private:
	Animation animation;
	Animation behingHitAnimation;
	Body* body;
	World*world;

	int health;
	
	Player* player;

	float stateTime; //used for flipping skree 
	
	float bulletStateTime;

	float boomerangStateTime;

	float lastShot;

	std::vector<KraidBullet> bullets;
	std::vector<KraidBullet> boomerangs;
	Animation boomerangAnimation;


	float hitBulletTime; //used when being hit by bullet

public:
	Kraid();
	~Kraid();
	void Create(World *world, Texture *texture, Player*player, int x, int y);

	void Create(World *world, Texture *texture, Player*player, Body* body);

	void HandlePhysics();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void OnHitBullet();

	void OnHitBomb();

	bool IsDead();

};

