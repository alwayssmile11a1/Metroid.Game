#include "MetroidGame.h"

MetroidGame::MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
	:Game(hInstance, windowName, screenWidth, screenHeight, isFullScreen, frameRate)
{

}
MetroidGame::~MetroidGame()
{
	batch.Release();
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


	cam.SetPosition(0, 0);
	cam.SetSize(640, 480);

	batch.SetCamera(&cam);

	texture = Texture(L"Resources/DemoScreen05.jpg");
	sprite = Sprite(&texture);
	sprite.SetSize(1000, 480);
	sprite.SetPosition(sprite.GetSize().X/2-320, 0);

	texture2 = Texture(L"Resources/character.png");
	sprite2 = Sprite(&texture2, -220, -120, 0, 0, 75, 86, 75, 86);
	ani = Animation(&sprite2, 27, 7, 20);
	//sprite2.SetRotation(sprite.GetRotation() + 20);
}

void MetroidGame::Resize(float x, float y)
{
	cam.Resize(x, y);
}

void MetroidGame::UpdateGame(float dt)
{

	//sprite.SetRotation(sprite.GetRotation()+5*dt);

	if (Input::GetKey(DIK_RIGHT))
	{
		ani.Next(dt, true);
		ani.GetKeyAnimation()->SetPosition(ani.GetKeyAnimation()->GetPosition().X+dt*0.15, ani.GetKeyAnimation()->GetPosition().Y);
	}

	if (Input::GetKey(DIK_LEFT))
	{
		ani.Next(dt, false);
		ani.GetKeyAnimation()->SetPosition(ani.GetKeyAnimation()->GetPosition().X - dt*0.15, ani.GetKeyAnimation()->GetPosition().Y);
	
	}

	if(ani.GetKeyAnimation()->GetPosition().X > cam.GetPosition().X)
	{
		cam.SetPosition(ani.GetKeyAnimation()->GetPosition().X, cam.GetPosition().Y);
	}

	if (ani.GetKeyAnimation()->GetPosition().X < cam.GetPosition().X - 250 && cam.GetPosition().X>0)
	{
		cam.SetPosition(cam.GetPosition().X-dt*0.15, cam.GetPosition().Y);
	}

	

	if (Input::GetKey(DIK_UP))
	{	
		cam.SetPosition(cam.GetPosition().X, cam.GetPosition().Y + +dt*0.2);
	}

	if (Input::GetKey(DIK_DOWN))
	{
		cam.SetPosition(cam.GetPosition().X, cam.GetPosition().Y - dt * 0.2);
	}

	if (Input::GetKeyDown(DIK_ESCAPE))
	{
		Input::ShutDownApplication();
	}


	batch.Begin();


	batch.Draw(sprite);
	//batch.Draw(sprite2);
	batch.Draw(*ani.GetKeyAnimation());

	


	batch.End();

}
