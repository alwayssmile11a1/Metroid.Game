#include "MetroidGame.h"

MetroidGame::MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
	:Game(hInstance, windowName, screenWidth, screenHeight, isFullScreen, frameRate)
{

}
MetroidGame::~MetroidGame()
{
	batch.Release();
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
	batch.Create();

	////this is example 
	//world = World(100, 100, DeltaTime);
	/*obj = Object(300, 300, 10, 10);
	obj.SetVelocity(Vector2(0.1f,0));*/
	//obj.SetTexture(ani.GetKeyAnimation());
	//world.AddObject(obj);

	texture = Texture(L"Resources/DemoScreen05.jpg");
	sprite = Sprite(&texture);
	sprite.SetSize(640, 480);

	texture2 = Texture(L"Resources/character.png");
	sprite2 = Sprite(&texture2, 300, 300, 0, 0, 75, 86, 75, 86);
	ani = Animation(&sprite2, 27, 7, 20);

}

void MetroidGame::UpdateGame()
{
	if (Input::GetKey(DIK_RIGHT))
	{
		ani.Next(DeltaTime, true);
	}

	if (Input::GetKey(DIK_LEFT))
	{
		ani.Next(DeltaTime, false);
	}

	if (Input::GetKeyDown(DIK_ESCAPE))
	{
		Input::ShutDownApplication();
	}


	batch.Begin();


	batch.Draw(sprite);

	batch.Draw(*ani.GetKeyAnimation());

	


	batch.End();

	

}