#pragma once
#include "HanabiScene.h"
#include "HanabiWorld.h"
#include "HanabiSprite.h"
#include "HanabiMap.h"
#include "Player.h"
#include "WorldListener.h"
#include "HanabiSound.h"
#include "Skree.h"
#include "Zoomer.h"
#include "HanabiShape.h"
#include "Platform.h"

class PlayScene: public Scene
{
private:

	//CSound *BrinstarTheme = NULL;
	//CSound *Jump = NULL;

	//Camera
	Camera cam;
	//load map
	TMXLoader mapLoader;
	TMXMap* map;
	//world
	World world;

	//player
	Player player;
	//listen to collision between bodies
	WorldListener worldListener;

	//draw texture, sprite, ...
	SpriteBatch* batch;

	//enemy
	Skree skree;
	Texture skreeTexture;
	Zoomer zoomer;
	Texture zoomerTexture;

public:
	PlayScene();
	~PlayScene();

	void SetBatch(SpriteBatch* batch);
	void HandlePhysics(float dt);
	void Render();

	void Create() override;
	void Update(float dt) override;
	void Release() override;
};

