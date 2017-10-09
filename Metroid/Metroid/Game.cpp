#include"Game.h"
#include"Utility.h"

Game::Game()
{

}

Game::Game(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
{
	this->_HInstance = hInstance;
	this->_WindowName = windowName;
	this->_IsFullScreen = isFullScreen;
	this->_FrameRate = frameRate;
	this->_ScreenWidth = screenWidth;
	this->_ScreenHeight = screenHeight;
	_BackGroundColor = D3DCOLOR_XRGB(0, 0, 0);
	_BackGroundFilePath = NULL;
	_HWnd = NULL;
	_Backbuffer = NULL;
	_Background = NULL;
}

Game::~Game()
{
	//free the backbuffer
	if (_Backbuffer != NULL)
	{
		_Backbuffer->Release();
		_Backbuffer = NULL;
	}

	//free the _Background
	if (_Background != NULL)
	{
		_Background->Release();
		_Background = NULL;
	}

	//Release DirectXDevice
	DirectXDevice::Release();

	//Release input
	Input::Release();

}

void Game::SetBackGroundColor(D3DCOLOR color)
{
	_BackGroundColor = color;
}

void Game::SetBackGroundImage(LPWSTR filePath)
{
	_BackGroundFilePath = filePath;

	//Release first for sure
	_Background->Release();
	_Background = NULL;

	if (_BackGroundFilePath == NULL)
	{
		// Create background
		DirectXDevice::D3Ddevice->CreateOffscreenPlainSurface(
			100,					// width 				
			100,					// height
			D3DFMT_X8R8G8B8,		// format
			D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
			&_Background,
			NULL);
	}
	else
	{
		_Background = CreateSurfaceFromFile(DirectXDevice::D3Ddevice, _BackGroundFilePath);
	}
}

LRESULT CALLBACK Game::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool Game::InitWindow()
{
	//create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	//fill in the struct paramaters
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _HInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _WindowName;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	//Window style
	DWORD WINDOWSTYLE;
	if (_IsFullScreen)
	{
		WINDOWSTYLE = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; //should use this for full screen mode
	}
	else
	{
		WINDOWSTYLE = WS_OVERLAPPEDWINDOW; //should use this for window mode
	}

	//create the window
	_HWnd = CreateWindowEx(NULL,
		_WindowName,	//nam of window class
		_WindowName,	//title bar
		WINDOWSTYLE,	//window style
		CW_USEDEFAULT, //x position of window
		CW_USEDEFAULT, //y position of window
		_ScreenWidth, //width of the window
		_ScreenHeight, //height of the window,
		NULL, //parent window = none
		NULL, //menu = none
		_HInstance, //application Instance
		NULL //window parameters
	);

	//if something bad happened, return
	if (!_HWnd)
		return false;

	//display the window
	ShowWindow(_HWnd, SW_SHOWNORMAL);
	UpdateWindow(_HWnd);

	return true;
}


bool Game::InitDirectX()
{

	//DirectXDevice::Init(_HWnd,_IsFullScreen,_ScreenWidth,_ScreenHeight);
	if(!DirectXDevice::Init(_HWnd, _IsFullScreen, _ScreenWidth, _ScreenHeight)) return false;

	//set random number seed
	srand(time(NULL));

	//clear the backbuffer to black
	DirectXDevice::D3Ddevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);


	// Create background
	DirectXDevice::D3Ddevice->CreateOffscreenPlainSurface(
		100,					// width 				
		100,					// height
		D3DFMT_X8R8G8B8,		// format
		D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
		&_Background,
		NULL);


	//return okay
	return true;
}

void Game::InitGame()
{
	//init window
	if (!InitWindow())
	{
		return;
	}
	
	//init directX
	if (!InitDirectX())
	{
		return;
	}

	//init input manager
	Input::Init(_HInstance, _HWnd);

	//create game
	CreateGame();
}

int Game::RunGame()
{
	//message from window
	MSG msg;

	//a variable to let us know the starting time of a frame
	DWORD frame_start = GetTickCount();
	//the average time per frame
	DWORD count_per_frame = 1000 / _FrameRate;

	//game loop
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			//Translate message and dispatch to WinProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			//wanna quit?
			if (msg.message == WM_QUIT)
				break;
		}
		
		Input::ProcessKeyBoardInformation();
		Input::ProcessMouseInformation();

		//get "now" time
		DWORD now = GetTickCount();
		//calculate delta time
		DeltaTime = now - frame_start;
		if (DeltaTime >= count_per_frame) //if true, next frame
		{

			frame_start = now;

			//make sure the Direct3D device is valid
			if (DirectXDevice::D3Ddevice == NULL)
			{
				return 0;
			}

			//start rendering
			if (DirectXDevice::D3Ddevice->BeginScene())
			{
				//Clear back ground with a colored surface
				if (_BackGroundFilePath == NULL)
				{
					// Fill the bitmap
					DirectXDevice::D3Ddevice->ColorFill(_Background, NULL, _BackGroundColor);

					// Draw the surface onto the back buffer
					DirectXDevice::D3Ddevice->StretchRect(
									_Background,			// from 
									NULL,				// which portion?
									_Backbuffer,		// to 
									NULL,				// which portion?
									D3DTEXF_NONE);
				}
				else //Clear back ground with an image
				{
	
					//draw surface to backbuffer
					DirectXDevice::D3Ddevice->StretchRect(_Background, NULL, _Backbuffer, NULL, D3DTEXF_NONE);
				}

				UpdateGame();

				//clear buffedInput after we has done update game
				Input::ClearKeyBoardBuffedInput();

				//create pointer to the backbuffer
				DirectXDevice::D3Ddevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_Backbuffer);

				//stop rendering
				DirectXDevice::D3Ddevice->EndScene();
			}

			//Display the backbuffer on the screen
			DirectXDevice::D3Ddevice->Present(NULL, NULL, NULL, NULL);

		}
		else
		{
			//sleep
			Sleep(count_per_frame - (now - frame_start));
		}

	}

	return msg.wParam;

}


