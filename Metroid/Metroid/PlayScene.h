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
<<<<<<< HEAD
#include "HanabiSpaceDivisionQuadTree.h"
=======
#include "Rio.h"
>>>>>>> 92ddb9dc936e10263078a575922efbe7f7601c93

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
<<<<<<< HEAD

	SpaceDivisionQuadTree sdQuadTree;

=======
	Zoomer zoomer;
	Texture zoomerTexture;
	Rio rio;
	Texture rioTexture;
>>>>>>> 92ddb9dc936e10263078a575922efbe7f7601c93
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

