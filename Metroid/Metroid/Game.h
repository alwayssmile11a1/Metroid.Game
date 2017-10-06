#pragma once

#include "stdafx.h"

//macro used for reading keys
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)

//this abstract class manages game structure, such as DirectX, game run, etc... 
class Game
{
private:
	//Window related variables
	HINSTANCE _HInstance; //handle for a window instance
	HWND _HWnd;				// Handle of the Game Window
	LPWSTR _WindowName; //the application title
	bool _IsFullScreen; //fullscreen or not?
	int _FrameRate; //how many frames in one second?
	int _ScreenWidth;
	int _ScreenHeight;

	//time between two frames
	DWORD DeltaTime;

	//Direct3D variables
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	LPDIRECT3DSURFACE9 _Backbuffer;
	LPDIRECT3DSURFACE9 _Background;
	D3DCOLOR _BackGroundColor;
	LPWSTR _BackGroundFilePath;
	bool _IsCreatedBackGround; //this variable help us to identify whether we have already create background image from file or haven't

	//window event callback function - basically we use this function to determine what message is sent to Window
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	//init
	bool InitWindow();
	bool InitDirectX();

protected:
	//RECOMMEND: overide these two function and do all the things you want

	//create all the things of a game here, such as world, object, ...
	void virtual CreateGame() = 0;
	//update game by one frame (render, control game) - just write your game here
	void virtual UpdateGame() = 0;

	//useful function
	DWORD GetDeltaTime();
	LPDIRECT3DDEVICE9 GetDevice();
	//set background color. If you have already set background image, this function has no affect at all
	void SetBackGroundColor(D3DCOLOR color);
	//create a background from this image. If you want to disable this function, just set the filePath to be NULL
	void SetBackGroundImage(LPWSTR filePath);

public:
	//constructor and destructor
	Game();
	Game(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate);
	~Game();

	//RECOMMEND: don't modify this function, just call it in the main function
	//init all the things we need to start drawing our game
	void InitGame();

	//RECOMMEND: don't modify this function, just call it in the main function
	//do things in the updateGame function
	//and this function will take care the rest for you
	int RunGame();

};


