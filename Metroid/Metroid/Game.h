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
	LPDIRECT3DSURFACE9 backbuffer;
	LPDIRECT3DSURFACE9 background;

	//window event callback function - basically we use this function to determine what message is sent to Window
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	//init
	bool InitWindow();
	bool InitDirectX();

protected:

	//useful function
	DWORD GetDeltaTime();
	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DSURFACE9 GetBackground();

	//RECOMMEND: overide these two function and do all the things you want
	//create all the things of a game here, such as world, object, ...
	void virtual CreateGame() = 0;
	//update game by one frame (render, control game) - just write your game here
	void virtual UpdateGame() = 0;

public:
	//constructor and destructor
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


