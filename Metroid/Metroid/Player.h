#pragma once
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "Bullet.h"
#include <vector>
#include "CollisionBit.h"
#include "HanabiStateManager.h"
#include "Bomb.h"
#include "HanabiSound.h"
#include "HanabiInput.h"
#define FIRERATE 0.1
#define MAXJUMPTIME 0.5
#define MAXUNTOUCHABLETIME 0.3 
#define MAXDEADTIME 0.5

//Main character
class Player : public Sprite
{
private:
	Texture texture;

	//Animation
	Animation appearingAnimation;
	Animation standingAnimation;
	Animation movingAnimation;
	Animation jumpingAnimation;
	Animation standAndShootupAnimation;
	Animation moveAndShootAnimation;
	Animation moveAndShootupAnimation;
	Animation jumpAndShootupAnimation;
	Animation jumpAndShootAnimation;
	Animation rollingAnimation;
	Animation jumpAndRollAnimation;
	Animation beingHitAnimation;

	StateManager characterStateManager;

	//Body
	Body* mainBody;
	Body* foot;
	Body* head;

	//deadEffect
	std::vector<Sprite> deadEffect;

	//bullets
	std::vector<Bullet*> bullets;

	//bomb
	Bomb* bomb;

	World* world;
	
	//
	float lastShot;

	float jumpTime;

	bool isGrounded;
	bool isLookingup;
	bool isShooting;
	bool isRolling;
	bool isHeadHit;
	bool isBombing;
	int health;

	bool canRoll;
	bool canBomb;

	float beingHitTime;
	bool beingRightHit;

	float deadTime;

	//sound
	CSound *itemAcquisition=NULL;
	CSound *jump = NULL;
	CSound *move = NULL;
	CSound *appearance = NULL;
	CSound *fire = NULL;
	CSound *death = NULL;
public:


public:
	Player();
	~Player();

	void Create(World *world, float x, float y);

	void HandleInput();

	void Render(SpriteBatch *batch);

	void Update(float dt);

	void Fire();

	void OnAppearing(float dt);

	void OnGrounded();

	void OnHitRollItem();
	
	void OnHitBombItem();

	void OnHitHealthItem();

	void OnHitEnemy(bool rightHit);

	void OnHeadHit();

	int GetHealth();
	
	bool IsDead();

	Body* GetMainBody();

	void Release();

	bool getisGrounded();

};

