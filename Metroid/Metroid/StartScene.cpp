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
	regions = p.GetRegion("startscene");
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
	//batch->Draw(*startSceneTexture, 0, 0,500,500);
	if (Input::GetKeyDown(DIK_DOWN))
	{
		background.SetRegion(regions.at(1));
	}
	if (Input::GetKeyDown(DIK_UP))
	{
		background.SetRegion(regions.at(0));
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
