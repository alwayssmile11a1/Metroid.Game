#pragma once
#include "stdafx.h"
#include "Game.h"
#include "Object.h"
#include "World.h"

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

	Game game = Game(hInstance, APPTITLE, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREENMODE, FRAME_RATE);
	game.initGame();
	game.runGame();

}