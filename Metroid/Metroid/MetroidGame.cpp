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

	// 1/intro scene
	introScene.Create();
	introScene.SetBatch(&batch);

	// 2/start scene
	startScene.Create();
	startScene.SetBatch(&batch);

	// 3/play screen
	playScene.Create();
	playScene.SetBatch(&batch);

	// 4/gameover scene
	gameOverScene.Create();
	gameOverScene.SetBatch(&batch);


	SetScene(&introScene);
	scenes = &introScene;
	pauseTime = 0;
}
void MetroidGame::UpdateGame(float dt)
{
	Game::UpdateGame(dt);
	
	if (Input::GetKeyDown(DIK_ESCAPE))
	{
		ShutDownApplication();
	}
	if (Input::GetKeyDown(DIK_RETURN))
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
			Sound::Stop(&introScene.GetSound());
			scenes = &playScene;
		}
	}
	if (playScene.isOver() == true)
	{
		pauseTime += 1;

		if (pauseTime > 50)
		{
			SetScene(&gameOverScene);
			gameOverScene.SetBatch(&batch);
			scenes = &gameOverScene;
		}
	}


}

void MetroidGame::Release()
{
	Game::Release();
	batch.Release();
	playScene.Release();
}

