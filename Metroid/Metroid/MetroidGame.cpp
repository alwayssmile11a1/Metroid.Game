#include "MetroidGame.h"
#include "HanabiSpaceDivisionQuadTree.h"

MetroidGame::MetroidGame(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
	:Game(hInstance, windowName, screenWidth, screenHeight, isFullScreen, frameRate)
{

}
MetroidGame::~MetroidGame()
{
	
}


void MetroidGame::CreateGame()
{
	SpaceDivisionQuadTree quad;
	quad.BuildTreeNodesFromTMX("Resources/map3SDQuadTree.xml", "Resources/map3.tmx");


	//quad.Load("Resources/mytest.xml");

	//create batch to draw everything
	batch.Create();

	//play screen
	playScene.Create();
	playScene.SetBatch(&batch);


	//intro scene
	introScene.Create();
	introScene.SetBatch(&batch);

	//start scene
	startScene.Create();
	startScene.SetBatch(&batch);
	//set screne which will be rendered
	SetScene(&introScene);
	scenes = &introScene;

}
void MetroidGame::UpdateGame(float dt)
{
	Game::UpdateGame(dt);

	if (input.GetKeyDown(DIK_ESCAPE))
	{
		ShutDownApplication();
	}
	if (input.GetKeyDown(DIK_RETURN))
	{
		if (scenes == &introScene)
		{
			SetScene(&startScene);
			startScene.SetBatch(&batch);
			scenes = &startScene;
		}
		else if (scenes == &startScene)
		{
			SetScene(&playScene);
			playScene.SetBatch(&batch);
			scenes = &playScene;
		}
	}


}

void MetroidGame::Release()
{
	Game::Release();
	batch.Release();
	playScene.Release();
}

