#include"Game.h"
#include"Utility.h"

Game::Game(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
{
	this->hInstance = hInstance;
	this->windowName = windowName;
	this->isFullScreen = isFullScreen;
	this->frameRate = frameRate;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	hWnd = NULL;
	d3d = NULL;
	d3ddev = NULL;
	backbuffer = NULL;
	background = NULL;
}

Game::~Game()
{
	//free the surface
	if (background != NULL)
	{
		background->Release();
	}

	//release the Direct3D device
	if (d3ddev != NULL) {
		d3ddev->Release();
	}

	//release the Direct3D object
	if (d3d != NULL)
		d3d->Release();
}

LPDIRECT3DDEVICE9 Game::GetDevice()
{
	return d3ddev;
}

LPDIRECT3DSURFACE9 Game::GetBackground()
{
	return background;
}

LRESULT CALLBACK Game::winProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

bool Game::initWindow()
{
	//create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	//fill in the struct paramaters
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)winProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = windowName;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	//Window style
	DWORD WINDOWSTYLE;
	if (isFullScreen)
	{
		WINDOWSTYLE = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; //should use this for full screen mode
	}
	else
	{
		WINDOWSTYLE = WS_OVERLAPPEDWINDOW; //should use this for window mode
	}

	//create the window
	hWnd = CreateWindowEx(NULL,
		windowName,	//nam of window class
		windowName,	//title bar
		WINDOWSTYLE,	//window style
		CW_USEDEFAULT, //x position of window
		CW_USEDEFAULT, //y position of window
		screenWidth, //width of the window
		screenHeight, //height of the window,
		NULL, //parent window = none
		NULL, //menu = none
		hInstance, //application Instance
		NULL //window parameters
	);

	//if something bad happened, return
	if (!hWnd)
		return false;

	//display the window
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	return true;
}


bool Game::initDirectX()
{
	HRESULT result;

	//initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL) {
		MessageBox(hWnd, L"Error initializing Direct3D", L"Error", MB_OK);
		return 0;
	}

	//set DIRECT3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (isFullScreen)
	{
		d3dpp.Windowed = false; //full screen or not?
	}
	else
	{
		d3dpp.Windowed = true;
	}
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = screenWidth;
	d3dpp.BackBufferHeight = screenHeight;
	d3dpp.hDeviceWindow = hWnd;

	//create Direct3D device
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
	);

	if (d3ddev == NULL) {
		MessageBox(hWnd, L"Error creating Direct3D device", L"Error", MB_OK);
		return 0;
	}

	//set random number seed
	srand(time(NULL));

	//clear the backbuffer to black
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	////create pointer to the backbuffer
	//d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	////create plain surface
	//result = d3ddev->CreateOffscreenPlainSurface(
	//	100, //width of the surface
	//	100, //height of the surface
	//	D3DFMT_X8R8G8B8, //surface format
	//	D3DPOOL_DEFAULT, //memory pool to use
	//	&surface, //pointer to the surface
	//	NULL //reserved (always NULL)
	//);	
	//if (!result)
	//	return 1;

	background = CreateSurfaceFromFile(d3ddev, L"DemoScreen05.jpg");

	//draw surface to backbuffer
	d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);


	//return okay
	return 1;
}

void Game::initGame()
{
	//init window
	if (!initWindow())
	{
		return;
	}
	
	//init directX
	if (!initDirectX())
	{
		return;
	}


	//init game 
	Test->LoadResources(GetDevice(), L"ball.bmp", L"ball.bmp", L"ball.bmp",GetBackground(), 1, 1);
	world.addObject(Test);

}

int Game::runGame()
{
	//message from window
	MSG msg;

	//a variable to let us know the starting time of a frame
	DWORD frame_start = GetTickCount();
	//the average time per frame
	DWORD count_per_frame = 1000 / frameRate;

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

		//get "now" time
		DWORD now = GetTickCount();
		//calculate delta time
		deltaTime = now - frame_start;
		if (deltaTime >= count_per_frame) //if true, next frame
		{
			frame_start = now;

			//make sure the Direct3D device is valid
			if (d3ddev == NULL)
			{
				return 0;
			}

			//start rendering
			if (d3ddev->BeginScene())
			{
				updateGame();

				//create pointer to the backbuffer
				d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

				//stop rendering
				d3ddev->EndScene();
			}

			//Display the backbuffer on the screen
			d3ddev->Present(NULL, NULL, NULL, NULL);

		}
		else
		{
			//sleep
			Sleep(count_per_frame - (now - frame_start));
		}

	}

	return msg.wParam;

}

void Game::updateGame()
{

		//draw background
		d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);

		//update World 
		world.update(deltaTime, d3ddev, backbuffer);
		//d3ddev->ColorFill(surface, NULL, D3DCOLOR_XRGB(r, g, b));
		//
		//rect.left += dt*object.getVelocity().getX();
		//rect.right += dt*object.getVelocity().getY();

		////draw the surface to the backbuffer
		//d3ddev->StretchRect(surface, NULL, backbuffer, &rect, D3DTEXF_NONE);

		//check for escape key (to exit program)
		if (KEY_DOWN(VK_ESCAPE))
		{
			PostMessage(hWnd, WM_DESTROY, 0, 0);

		}

}

