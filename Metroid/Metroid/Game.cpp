#include"Game.h"
#include"Utility.h"

Game::Game(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate)
{
	this->_HInstance = hInstance;
	this->_WindowName = windowName;
	this->_IsFullScreen = isFullScreen;
	this->_FrameRate = frameRate;
	this->_ScreenWidth = screenWidth;
	this->_ScreenHeight = screenHeight;

	_HWnd = NULL;
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

DWORD Game::GetDeltaTime()
{
	return DeltaTime;
}

LPDIRECT3DDEVICE9 Game::GetDevice()
{
	return d3ddev;
}

LPDIRECT3DSURFACE9 Game::GetBackground()
{
	return background;
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
	HRESULT result;

	//initialize Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL) {
		MessageBox(_HWnd, L"Error initializing Direct3D", L"Error", MB_OK);
		return 0;
	}

	//set DIRECT3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (_IsFullScreen)
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
	d3dpp.BackBufferWidth = _ScreenWidth;
	d3dpp.BackBufferHeight = _ScreenHeight;
	d3dpp.hDeviceWindow = _HWnd;

	//create Direct3D device
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_HWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
	);

	if (d3ddev == NULL) {
		MessageBox(_HWnd, L"Error creating Direct3D device", L"Error", MB_OK);
		return 0;
	}

	//set random number seed
	srand(time(NULL));

	//clear the backbuffer to black
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);


	//return okay
	return 1;
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

		//get "now" time
		DWORD now = GetTickCount();
		//calculate delta time
		DeltaTime = now - frame_start;
		if (DeltaTime >= count_per_frame) //if true, next frame
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
				UpdateGame();

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


