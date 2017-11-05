#pragma once
#include "stdafx.h"
#include "Game.h"
#include "World.h"
#include "Animation.h"
#include "SpriteBatch.h"
#include "TexturePacker.h"
#include "Collision.h"
#include "TMXLoader.h"
#include "Object.h"

class MetroidGame: public Game, public WorldContactListener
{
private:
	Animation ani;
	SpriteBatch batch;
	Texture characterTexture;
	//Sprite characterSprite;
	//Sprite characterSprite2;
	//Sprite characterSprite3;
	bool isGrounded = false;
	bool isJumped = false;

	Camera cam;

	TMXLoader mapLoader;
	TMXMap* map;


	World world;

	Object object1;
	Object object2;
	Object object3;

	Body foot;

protected:
	//create all the things of a game here, such as world, object, ...
	void CreateGame();
	//update game by one frame (render, control game) - just write your game here
	void UpdateGame(float dt);

	//Override OnContact of WorldContactListener
	void OnContact(const Body &bodyA, const Body &bodyB);

	void HandlePhysics(float dt);

	void Render();

public:
	MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate);
	~MetroidGame();

};