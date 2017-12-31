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
#include "Ripper.h"
#include "HanabiShape.h"
#include "Platform.h"
#include "HanabiSpaceDivisionQuadTree.h"
#include "MaruMariItem.h"
#include "HanabiLabel.h"
#include "HealthItem.h"
#include "ExplosionEffect.h"
#include "BombItem.h"
#include "BreakablePlatform.h"
#include "Rio.h"
#include "MotherBrain.h"
#include "Cannon.h"
#include "HealthPile.h"
#include "CircleCannon.h"
#include "Kraid.h"
#include "Door.h"

#define PLAYERAPPEARINGTIME 3

class PlayScene: public Scene
{
private:

	float stateTime;
	//Sound sound;
	CSound *BrinstarTheme = NULL;
	//CSound *Jump = NULL;

	//Camera
	Camera cam;
	//load map
	TMXLoader mapLoader;
	TMXMap* map;
	//world
	World world;
	//quadtree
	SpaceDivisionQuadTree sdQuadTree;

	//player
	Player player;
	Vector2 initPlayerPosition;
	//listen to collision between bodies
	WorldListener worldListener;

	//draw texture, sprite, ...
	SpriteBatch* batch;

	
	std::vector<BreakablePlatform*> breakablePlatforms;

	//Door
	Texture doorTexture;
	std::vector<Door*> doors;

	Door* kraidDoor;
	Door* motherBrainDoor;

	//enemies
	Texture enemiesTexture;

	std::vector<Skree*> skrees;
	std::vector<Zoomer*> zoomers;
	std::vector<Rio*> rios;
	std::vector<Ripper*>rippers;

	//bosses
	Texture bossesTexture;
	MotherBrain* motherBrain;
	Kraid *kraid;
	std::vector<Cannon*> cannons;
	std::vector<CircleCannon*> circleCannons;
	std::vector<HealthPile*> healthPiles;



	//UI
	Font font;
	Label playerHealthLabel;

	//Items
	Texture itemsTexture;
	MaruMariItem maruMariItem;
	BombItem bombItem;
	std::vector<HealthItem*> healthItems;


	//Effect
	Texture effectsTexture;
	ExplosionEffect explosionEffect;

	float passTime; // the time the player need to pass the door
	
	float kraidDoorPassTime; 
	float motherBrainDoorPassTime;


public:
	PlayScene();
	~PlayScene();

	void SetBatch(SpriteBatch* batch);
	void HandlePhysics(float dt);
	void Render();

	void Create() override;
	void Update(float dt) override;
	void Release() override;
	bool isOver();
	CSound *GetSound();
};

