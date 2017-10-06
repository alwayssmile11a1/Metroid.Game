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
	//SetBackGroundImage(L"DemoScreen05.JPG");
	//world = World(100, 100, GetDeltaTime());
	obj = new Object(20, 20, 10, 10);
	obj->SetVelocity(Vector2(0.1f,0));
	ani = Animation(GetDevice(), L"1704.png", 27, 44, 5, 5);
	//sample = Sprite(GetDevice(), L"ball.png", 200, 200);
	//world.AddObject(obj);
}

void MetroidGame::UpdateGame()
{
	obj->_Position.SetX(GetDeltaTime()*obj->_Velocity.GetX() + obj->_Position.GetX());
	obj->_Position.SetY(GetDeltaTime()*obj->_Velocity.GetY() + obj->_Position.GetY());
	obj->SetTexture(ani.GetKeyAnimation());
	ani.Next();
	obj->Update(GetDeltaTime());
	//world.Update(GetDeltaTime());
	//sample.Render();
}