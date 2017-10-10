#pragma once
#include "stdafx.h"
#include "Game.h"
#include "Sprite.h"
#include "World.h"
#include "Animation.h"
#include "SpriteBatch.h"

class MetroidGame: Game
{
private:
	World world;
	Object obj;
	Animation ani;
	SpriteBatch batch;
	Texture texture;
	Sprite sprite;

protected:
	//create all the things of a game here, such as world, object, ...
	void CreateGame();
	//update game by one frame (render, control game) - just write your game here
	void UpdateGame();

public:
	MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate);
	~MetroidGame();

	void InitGame();
	void RunGame();

};