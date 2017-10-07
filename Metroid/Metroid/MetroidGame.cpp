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
	//this is example 
	SetBackGroundImage(L"DemoScreen05.JPG");
	world = World(100, 100, GetDeltaTime());
	obj = Object(10, 300, 10, 10);
	obj.SetVelocity(Vector2(0.1f,0));
	ani = Animation(GetDevice(), L"character.png", 75, 86, 27, 7, 20);
	obj.SetTexture(ani.GetKeyAnimation());
	//a = ani.GetKeyAnimation();
	//sample = Sprite(GetDevice(), L"ball.png", 200, 200);
	world.AddObject(obj);
}

void MetroidGame::UpdateGame()
{
	if (Input::GetKey(DIK_RIGHT))
	{
		obj._Position.SetX(GetDeltaTime()*obj._Velocity.GetX() + obj._Position.GetX());
		obj.SetTexture(ani.GetKeyAnimation());
		ani.Next(GetDeltaTime());
	}

	////obj->Update(GetDeltaTime());
	////ani.Next(GetDeltaTime());
	////ani.Render(100,100);
	world.Update(GetDeltaTime());

	//sample.Render();
}