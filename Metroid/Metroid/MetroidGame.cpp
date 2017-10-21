#include "MetroidGame.h"

MetroidGame::MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
	:Game(hInstance, windowName, screenWidth, screenHeight, isFullScreen, frameRate)
{

}
MetroidGame::~MetroidGame()
{
	batch.Release();
}

void MetroidGame::CreateGame()
{
	batch.Create();
	cam.SetPosition(0, 0);
	batch.SetCamera(&cam);

	backGroundTexture = Texture(L"Resources/DemoScreen05.jpg");
	backGroundSprite = Sprite(&backGroundTexture);
	backGroundSprite.SetSize(1000, 480);
	backGroundSprite.SetPosition(backGroundSprite.GetSize().X/2-320, 0);

	characterTexture = Texture(L"Resources/samusaran_sheet.png");
	characterSprite = Sprite(&characterTexture, -110, -120, 244, 36, 17, 33, 34, 66);

	/*ani.AddRegion(TextureRegion(&characterTexture,244, 36, 17, 33));
	ani.AddRegion(TextureRegion(&characterTexture,283, 36, 19, 34));
	ani.AddRegion(TextureRegion(&characterTexture,322, 36, 22, 34));*/
	
	TexturePacker p = TexturePacker(&characterTexture, "Resources/samusaran_packer.txt");
	ani.AddRegion(p.GetRegion("charactermove"));
	

}

void MetroidGame::UpdateGame(float dt)
{

	if (input.GetKey(DIK_RIGHT))
	{
		characterSprite.SetRegion(ani.Next(dt, true));
		characterSprite.SetPosition(characterSprite.GetPosition().X+dt*0.2, characterSprite.GetPosition().Y);
	}        

	if (input.GetKey(DIK_LEFT))
	{
		characterSprite.SetRegion(ani.Next(dt, false));
		characterSprite.SetPosition(characterSprite.GetPosition().X - dt*0.2, characterSprite.GetPosition().Y);
	}

	if(characterSprite.GetPosition().X > cam.GetPosition().X)
	{
		cam.SetPosition(characterSprite.GetPosition().X, cam.GetPosition().Y);
	}

	if (characterSprite.GetPosition().X < cam.GetPosition().X - 250 && cam.GetPosition().X>0)
	{
		cam.SetPosition(cam.GetPosition().X-dt*0.2, cam.GetPosition().Y);
	}

	if (input.GetKey(DIK_UP))
	{	
		cam.SetPosition(cam.GetPosition().X, cam.GetPosition().Y + +dt*0.2);
	}

	if (input.GetKey(DIK_DOWN))
	{
		cam.SetPosition(cam.GetPosition().X, cam.GetPosition().Y - dt * 0.2);
	}

	if (input.GetKeyDown(DIK_ESCAPE))
	{
		input.ShutDownApplication();
	}


	batch.Begin();


	batch.Draw(backGroundSprite);
	batch.Draw(characterSprite);
	

	batch.End();

}
