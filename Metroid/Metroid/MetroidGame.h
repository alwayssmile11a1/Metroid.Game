#pragma once
#include "stdafx.h"
#include "Game.h"
#include "World.h"
#include "Animation.h"
#include "SpriteBatch.h"
#include "TexturePacker.h"
#include "Collision.h"
#include "TMXLoader.h"

class MetroidGame: public Game
{
private:
	Animation ani;
	SpriteBatch batch;
	Texture characterTexture;
	Texture backGroundTexture;
	Sprite characterSprite;
	Sprite characterSprite2;
	Sprite backGroundSprite;

	Camera cam;

	TMXLoader mapLoader;
	TMXMap* map;

protected:
	//create all the things of a game here, such as world, object, ...
	void CreateGame();
	//update game by one frame (render, control game) - just write your game here
	void UpdateGame(float dt);

	//void Resize(float x, float y);

public:
	MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate);
	~MetroidGame();

};