#pragma once
#include "stdafx.h"
#include "Game.h"
#include "Sprite.h"
#include "World.h"
#include "Animation.h"
#include "SpriteBatch.h"

class MetroidGame: public Game
{
private:
	Animation ani;
	SpriteBatch batch;
	Texture characterTexture;
	Texture backGroundTexture;
	Sprite characterSprite;
	Sprite backGroundSprite;

	Camera cam;

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