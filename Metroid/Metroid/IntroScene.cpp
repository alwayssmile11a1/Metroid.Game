#include "IntroScene.h"

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

void IntroScene::SetBatch(SpriteBatch* batch)
{
	this->batch = batch;
	//set the camera to be used by this batch
	batch->SetCamera(&cam);
}

void IntroScene::Create()
{
	cam.SetPosition(0, 0);
	introSceneTexture = Texture("Resources/intro.png");
	TexturePacker p = TexturePacker(&introSceneTexture, "Resources/introscene.xml");

	introSceneAnimation.AddRegion(p.GetRegion("introscene"));
	introSceneAnimation.SetFrameInterval(0.03);
//	background.SetRegion(&p.GetRegion("introscene").at(0));
	background.SetRegion(*introSceneAnimation.GetKeyAnimation());
	/*background = Sprite(&introSceneTexture);
	background.SetTexture(&introSceneTexture);*/
	background.SetSize(screenWidth, screenHeight);
	background.SetPosition(0, 0);
}


void  IntroScene::Update(float dt)
{
	//start drawing
	batch->Begin();
	batch->SetCamera(&cam);
	background.SetRegion(*introSceneAnimation.Next(dt));
	batch->Draw(background);
	//end drawing
	batch->End();

}

void IntroScene::Release()
{
	//delete IntroSceneTexture;
}
