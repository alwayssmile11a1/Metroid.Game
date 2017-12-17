#pragma once
#include "HanabiScene.h"
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "HanabiMap.h"
#include "HanabiInput.h"

class StartScene : public Scene
{
private:
	//Camera
	Camera cam;
	Sprite background;
	Animation startSceneAnimation;
	//draw texture, sprite, ...
	SpriteBatch* batch;

	Texture startSceneTexture;

	std::vector<TextureRegion> regions;

public:
	StartScene();
	~StartScene();

	void SetBatch(SpriteBatch* batch);

	void Create() override;
	void Update(float dt) override;
	void Release() override;	
};