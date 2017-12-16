#pragma once

#include "HanabiGame.h"
#include "PlayScene.h"
#include "IntroScene.h"
#include "StartScene.h"
class MetroidGame: public Game
{
private:
	SpriteBatch batch;
	PlayScene playScene;
	IntroScene introScene;
	StartScene startScene;
	Scene *scenes;
protected:
	//create all the things of a game here, such as world, object, ...
	void CreateGame() override;
	//update game by one frame (render, control game) - just write your game here
	void UpdateGame(float dt) override;


public:
	MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate);
	~MetroidGame();

	void Release() override;
};