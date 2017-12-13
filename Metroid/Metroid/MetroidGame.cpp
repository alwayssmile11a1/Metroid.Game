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
	
	//set screne which will be rendered
	SetScene(&playScene);

}
void MetroidGame::UpdateGame(float dt)
{

	Game::UpdateGame(dt);
	
	if (input.GetKeyDown(DIK_ESCAPE))
	{
		ShutDownApplication();
	}



}

void MetroidGame::Release()
{
	Game::Release();
	batch.Release();
	playScene.Release();
}

