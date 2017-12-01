#pragma once
#include "Scene.h"
#include "World.h"
#include "Animation.h"
#include "SpriteBatch.h"
#include "TexturePacker.h"
#include "Collision.h"
#include "TMXLoader.h"
#include "Player.h"
#include "WorldListener.h"
#include "MySound.h"
#include "Skree.h"
#include "Rectangle.h"
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

