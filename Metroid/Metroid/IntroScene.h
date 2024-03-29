#pragma once
#include "HanabiScene.h"
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "HanabiMap.h"
#include "HanabiSound.h"
class IntroScene : public Scene
{
private:
	//Camera
	Camera cam;
	CSound *TitleTheme = NULL;
	Sprite background;
	Animation introSceneAnimation;
	//draw texture, sprite, ...
	SpriteBatch* batch;

	Texture introSceneTexture;
public:
	IntroScene();
	~IntroScene();

	void SetBatch(SpriteBatch* batch);

	void Create() override;
	void Update(float dt) override;
	void Release() override;
	CSound *GetSound();//to stop in MetroidGame.cpp
	
};