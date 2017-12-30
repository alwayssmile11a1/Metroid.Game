#pragma once
#include "HanabiSprite.h"
#include "HanabiWorld.h"
#include "CollisionBit.h"
#include "HanabiSound.h"
class Door :public GameObject{
private:
	Animation doorAnimation;
	World *world;
	Body *bodyLeft;
	Body *bodyMid;
	Body *bodyRight;
	Texture doorTexture;

	Sprite left;
	Sprite right;

	bool isROpen;
	bool isLOpen;
	bool canPassLeft, canPassRight;

	float pauseTimeL,pauseTimeR;

	CSound *OpenNClose=NULL;
public:
	Door();
	~Door();
	//Door(World *world, float x, float y, float width, float height);
	void Create(World *world,Texture* doorTexture, int x, int y);
	void Render(SpriteBatch *batch);
	void Update(float dt);
	void LOnhitBullet();
	void ROnhitBullet();
	void SetLeftOpen(bool state);
	void SetRightOpen(bool state);
	bool IsLOpen();
	bool IsROpen();
	void SetCanPassRight(bool flag);
	bool GetCanPassRight();
	void SetCanPassLeft(bool flag);
	bool GetCanPassLeft();
};
