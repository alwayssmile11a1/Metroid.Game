//Manage game structure, such as DirectX, game_run, etc.
#pragma once

#include "stdafx.h"


//macro used for reading keys
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)



class Game
{
private:
	//Window related variables
	HINSTANCE hInstance; //handle for a window instance
	HWND hWnd;				// Handle of the Game Window
	LPWSTR windowName; //the application title
	bool isFullScreen; //fullscreen or not?
	int frameRate; //how many frames in one second?
	int screenWidth;
	int screenHeight;
	
	//time between two frames
	DWORD deltaTime;

	//Direct3D variables
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	LPDIRECT3DSURFACE9 backbuffer;
	LPDIRECT3DSURFACE9 surface;

	//window event callback function - basically we use this function to determine what message is sent to Window
	static LRESULT CALLBACK winProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool initWindow();
	bool initDirectX();

	//update game by one frame (render, control game)
	void updateGame();

public:
	//constructor and destructor
	Game(HINSTANCE hInstance, LPWSTR windowName, int screenWidth, int screenHeight, bool isFullScreen, int frameRate);
	~Game();

	//init all the things we need to start drawing our game
	void initGame();

	//run game
	int runGame();

	//maybe we play next time, shall we?
	void endGame();

};


