#include "MetroidGame.h"

MetroidGame::MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
	:Game(hInstance, windowName, screenWidth, screenHeight, isFullScreen, frameRate)
{

}
MetroidGame::~MetroidGame()
{
	delete obj;
	//obj = NULL;
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

	//world = World(100, 100, GetDeltaTime());
	obj = new Object(20, 20, 10, 10);
	obj->SetVelocity(Vector2(0.1f,0));
	sample = Sprite(GetDevice(), L"ball.png", 200, 200);
	obj->SetSprite(sample);
	//world.AddObject(obj);
}

void MetroidGame::UpdateGame()
{
	obj->_Position.SetX(GetDeltaTime()*obj->_Velocity.GetX() + obj->_Position.GetX());
	obj->_Position.SetY(GetDeltaTime()*obj->_Velocity.GetY() + obj->_Position.GetY());
	obj->Update(GetDeltaTime());
	//world.Update(GetDeltaTime());
	//sample.Render();
}