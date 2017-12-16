#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::SetBatch(SpriteBatch* batch)
{
	this->batch = batch;
	//set the camera to be used by this batch
	batch->SetCamera(&cam);
}

void GameOverScene::Create()
{
	cam.SetPosition(0, 0);
	gameOverSceneTexture = Texture("Resources/start.png");
	TexturePacker p = TexturePacker(&gameOverSceneTexture, "Resources/gameoverscene.xml");
	background.SetRegion(p.GetRegion("gameoverscene").at(0));
	background.SetSize(screenWidth, screenHeight);
	background.SetPosition(0, 0);
}


void  GameOverScene::Update(float dt)
{
	//start drawing
	batch->Begin();	
	batch->SetCamera(&cam);
	batch->Draw(background);
	//end drawing
	batch->End();

}

void GameOverScene::Release()
{
	//delete GameOverSceneTexture;
}
