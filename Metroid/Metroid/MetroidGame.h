#pragma once

#include "Game.h"
#include "World.h"
#include "Animation.h"
#include "SpriteBatch.h"
#include "TexturePacker.h"
#include "Collision.h"
#include "TMXLoader.h"
#include "Object.h"
#include "Player.h"
#include "WorldListener.h"
//#include "MySound.h"

class MetroidGame: public Game, public WorldContactListener
{
private:
	SpriteBatch batch;
	Camera cam;

	TMXLoader mapLoader;
	TMXMap* map;

	World world;

	Body* body1;
	Body* body2;

	Player player;

	WorldListener* worldListener;

protected:
	//create all the things of a game here, such as world, object, ...
	void CreateGame();
	//update game by one frame (render, control game) - just write your game here
	void UpdateGame(float dt);

	void HandlePhysics(float dt);

	void Render();

public:
	MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate);
	~MetroidGame();

	void Release();
};