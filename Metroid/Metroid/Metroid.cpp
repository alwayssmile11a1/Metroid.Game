#include "MetroidGame.h"

MetroidGame::MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
	:Game(hInstance, windowName, screenWidth, screenHeight, isFullScreen, frameRate)
{
	
}
MetroidGame::~MetroidGame()
{

}

void MetroidGame::InitGame()
{
	Game::InitGame();
}
void MetroidGame::RunGame()
{
	Game::RunGame();
}


void MetroidGame::CreateGame()
{
	//background = CreateSurfaceFromFile(d3ddev, L"DemoScreen05.jpg");

	////draw surface to backbuffer
	//d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);

	sample = Sprite(GetDevice(), L"ball.png", 200, 200);
}

void MetroidGame::UpdateGame()
{
	sample.Render();
	
}