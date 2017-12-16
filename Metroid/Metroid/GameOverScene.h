#pragma once
#include "HanabiScene.h"
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "HanabiMap.h"

class GameOverScene : public Scene
{
private:
	//Camera
	Camera cam;
	Sprite background;
	Animation gameOverSceneAnimation;
	//draw texture, sprite, ...
	SpriteBatch* batch;

	Texture gameOverSceneTexture;
public:
	GameOverScene();
	~GameOverScene();

	void SetBatch(SpriteBatch* batch);

	void Create() override;
	void Update(float dt) override;
	void Release() override;
};