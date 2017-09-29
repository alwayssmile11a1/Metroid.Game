#pragma once
#include "stdafx.h"
#include "Game.h"

// application title
//(since we use Unicode character set, //we have to put L before "Metroid". 
//This means the "Metroid" should be made of 16 bit Unicode characters, rather than 8 bit)
#define APPTITLE L"Metroid"

//Full screen or not
#define FULLSCREENMODE FALSE

//Screen resolution
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//frame rate 
#define FRAME_RATE 30



//The entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	Game game = Game(hInstance, APPTITLE, SCREEN_WIDTH, SCREEN_HEIGHT,FULLSCREENMODE, FRAME_RATE);
	game.initGame();
	game.runGame();




	//just leave this here for safe purpose//

	//MSG msg;

	////Register this window class - init window
	//MyRegisterClass(hInstance);

	////the handle for the window
	//HWND hWnd;

	////Window style
	//DWORD WINDOWSTYLE = WS_OVERLAPPEDWINDOW; //should use this for window mode
	//if(FULLSCREEN)
	//{
	//	WINDOWSTYLE = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; //should use this for full screen mode
	//}

	////create the window
	//hWnd = CreateWindowEx(NULL,
	//	APPTITLE,	//nam of window class
	//	APPTITLE,	//title bar
	//	WINDOWSTYLE,	//window style
	//	CW_USEDEFAULT, //x position of window
	//	CW_USEDEFAULT, //y position of window
	//	SCREEN_WIDTH, //width of the window
	//	SCREEN_HEIGHT, //height of the window,
	//	NULL, //parent window = none
	//	NULL, //menu = none
	//	hInstance, //application Instance
	//	NULL //window parameters
	//);

	////if something bad happened, return
	//if (!hWnd)
	//	return FALSE;

	////display the window
	//ShowWindow(hWnd, nCmdShow);
	//UpdateWindow(hWnd);

	////initialize Game - directX
	//if (!Game_Init(hWnd))
	//	return 0;

	////a variable to let us know the starting time of a frame
	//DWORD frame_start = GetTickCount();
	////the average time per frame
	//DWORD count_per_frame = 1000 / FRAME_RATE;


	////game loop
	//while (true)
	//{
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	//	{

	//		//Translate message and dispatch to WinProc
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);

	//		//wanna quit?
	//		if (msg.message == WM_QUIT)
	//			break;
	//	}

	//	//get "now" time
	//	DWORD now = GetTickCount();
	//	//calculate delta time
	//	dt = now - frame_start;
	//	if (dt >= count_per_frame) //if true, next frame
	//	{
	//		frame_start = now;
	//		Game_Run(hWnd);
	//	}
	//	else
	//	{
	//		//sleep
	//		Sleep(count_per_frame - dt);
	//	}

	//}

	//return msg.wParam;
}

////window event callback function - basically we use this function to determine what message is sent to Window
//LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	case WM_DESTROY:
//		Game_End(hWnd);
//		PostQuitMessage(0);
//		return 0;
//	default:
//		break;
//	}
//
//	return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
////just a function to help to create window
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	//create the window class structure
//	WNDCLASSEX wc;
//	wc.cbSize = sizeof(WNDCLASSEX);
//
//	//fill in the struct paramaters
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = (WNDPROC)WinProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = hInstance;
//	wc.hIcon = NULL;
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wc.lpszMenuName = NULL;
//	wc.lpszClassName = APPTITLE;
//	wc.hIconSm = NULL;
//
//	//Register this window class 
//	return RegisterClassEx(&wc);
//}
//
////Initialize Direct3D, back buffer, suface, etc.
//int Game_Init(HWND hwnd)
//{
//	HRESULT result;
//
//	//initialize Direct3D
//	d3d = Direct3DCreate9(D3D_SDK_VERSION);
//	if (d3d == NULL) {
//		MessageBox(hwnd, L"Error initializing Direct3D", L"Error", MB_OK);
//		return 0;
//	}
//
//	//set DIRECT3D presentation parameters
//	D3DPRESENT_PARAMETERS d3dpp;
//	ZeroMemory(&d3dpp, sizeof(d3dpp));
//	
//	if (FULLSCREEN)
//	{
//		d3dpp.Windowed = false; //full screen or not?
//	}
//	else
//	{
//		d3dpp.Windowed = true; 
//	}
//	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
//	d3dpp.BackBufferCount = 1;
//	d3dpp.BackBufferWidth = SCREEN_WIDTH;
//	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
//	d3dpp.hDeviceWindow = hwnd;
//
//	//create Direct3D device
//	d3d->CreateDevice(
//		D3DADAPTER_DEFAULT,
//		D3DDEVTYPE_HAL,
//		hwnd,
//		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//		&d3dpp,
//		&d3ddev
//	);
//
//	if (d3ddev == NULL) {
//		MessageBox(hwnd, L"Error creating Direct3D device", L"Error", MB_OK);
//		return 0;
//	}
//
//	//set random number seed
//	srand(time(NULL));
//
//	//clear the backbuffer to black
//	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
//
//	//create pointer to the backbuffer
//	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
//
//	////create plain surface
//	//result = d3ddev->CreateOffscreenPlainSurface(
//	//	100, //width of the surface
//	//	100, //height of the surface
//	//	D3DFMT_X8R8G8B8, //surface format
//	//	D3DPOOL_DEFAULT, //memory pool to use
//	//	&surface, //pointer to the surface
//	//	NULL //reserved (always NULL)
//	//);	
//	//if (!result)
//	//	return 1;
//
//	//load surface from file
//	result = D3DXLoadSurfaceFromFile(
//		surface, //destination surface
//		NULL, //destination pallete
//		NULL, //destination rectangle
//		L"bird.png", //Source file
//		NULL, //Source rectangle
//		D3DX_DEFAULT,
//		0,
//		NULL
//	);
//
//	//make sure the file was loaded properly
//	if (result != D3D_OK)
//		return 1;
//
//	//draw surface to backbuffer
//	d3ddev->StretchRect(surface, NULL, backbuffer, NULL, D3DTEXF_NONE);
//
//
//	//return okay
//	return 1;
//}
//
//
////Do your things here
//void Game_Run(HWND hwnd)
//{
//	//make sure the Direct3D device is valid
//	if (d3ddev == NULL)
//	{
//		return;
//	}
//
//	//clear the backbuffer to black
//	//d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
//
//
//	//start rendering
//	if (d3ddev->BeginScene())
//	{	
//
//		//d3ddev->ColorFill(surface, NULL, D3DCOLOR_XRGB(r, g, b));
//		//
//		//rect.left += dt*object.getVelocity().getX();
//		//rect.right += dt*object.getVelocity().getY();
//		
//		////draw the surface to the backbuffer
//		//d3ddev->StretchRect(surface, NULL, backbuffer, &rect, D3DTEXF_NONE);
//
//		//create pointer to the backbuffer
//		d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
//
//		//draw the surface to the backbuffer
//		d3ddev->StretchRect(surface, NULL, backbuffer,NULL, D3DTEXF_NONE);
//
//
//		//stop rendering
//		d3ddev->EndScene();
//	}
//
//	//Display the backbuffer on the screen
//	d3ddev->Present(NULL, NULL, NULL, NULL);
//
//	//check for escape key (to exit program)
//	if (KEY_DOWN(VK_ESCAPE))
//	{
//		PostMessage(hwnd, WM_DESTROY, 0, 0);
//		
//	}
//}
//
//void Game_End(HWND hwnd)
//{
//	
//	//free the surface
//	if (surface != NULL)
//	{
//		surface->Release();
//	}
//
//	//release the Direct3D device
//	if (d3ddev != NULL) {
//		d3ddev->Release();
//	}
//
//	//release the Direct3D object
//	if (d3d != NULL)
//		d3d->Release();
//
//}
