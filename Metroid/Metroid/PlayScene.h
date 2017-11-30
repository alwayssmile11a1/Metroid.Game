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

class PlayScene: public Scene
{
private:

	//CSound *BrinstarTheme = NULL;
	//CSound *Jump = NULL;

	Camera cam;

	TMXLoader mapLoader;
	TMXMap* map;

	World world;

	Body body1;
	Body body2;

	Player player;

	WorldListener worldListener;

	SpriteBatch* batch;

	
	

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

