#pragma once
#include "HanabiSprite.h"
#include "WorldListener.h"

class AirHole : public Sprite {
private:
	//Camera
	Camera cam;
	World *world;
	Animation airHoleAnimation;
	Body *body;
	//draw texture, sprite, ...
	SpriteBatch* batch;

	Texture airHoleTexture;
public:
	AirHole();
	~AirHole();

	//void SetBatch(SpriteBatch* batch);
	void Render(SpriteBatch *batch);
	void Create(World *world, Texture* doorTexture, int x, int y);
	void Update(float dt);
	void Release() ;
};