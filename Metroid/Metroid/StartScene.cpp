#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::SetBatch(SpriteBatch* batch)
{
	this->batch = batch;
	//set the camera to be used by this batch
	batch->SetCamera(&cam);
}

void StartScene::Create()
{
	cam.SetPosition(0, 0);
	startSceneTexture =  Texture("Resources/start.png"); 
	TexturePacker p = TexturePacker(&startSceneTexture, "Resources/startscene.xml");
	//background = Sprite(&startSceneTexture);
	//background.SetTexture(&startSceneTexture);
	background.SetRegion(p.GetRegion("startscene").at(0));
	background.SetSize(screenWidth,screenHeight);
	background.SetPosition(0,0);
}


void  StartScene::Update(float dt)
{
	//start drawing
	batch->Begin();
	startSceneTexture = Texture("Resources/start.png");
	TexturePacker p = TexturePacker(&startSceneTexture, "Resources/startscene.xml");
	//batch->Draw(*startSceneTexture, 0, 0,500,500);
	if (input.GetKeyDown(DIK_DOWN))
	{
		background.SetRegion(p.GetRegion("startscene").at(1));
	}
	if (input.GetKeyDown(DIK_UP))
	{
		background.SetRegion(p.GetRegion("startscene").at(0));
	}
	batch->SetCamera(&cam);
	batch->Draw(background);
	//end drawing
	batch->End();

}

void StartScene::Release()
{
	//delete startSceneTexture;
}
