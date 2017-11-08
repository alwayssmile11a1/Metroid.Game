#pragma once
#include "MetroidGame.h"

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
#define FRAME_RATE 60



//The entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	MetroidGame game(hInstance, APPTITLE, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREENMODE, FRAME_RATE);
	game.RunGame();
	game.Release();
}