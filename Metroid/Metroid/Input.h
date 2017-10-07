#pragma once
#include "stdafx.h"

#define KEYBOARD_BUFFER_SIZE	1024

class Input
{
private:
	 static LPDIRECTINPUT8       _DirectInput;		// The DirectInput object         
	 static LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 
	 static BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 

	 static DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data

	 static int _CurrentKeyCode;	//the current key code being checked in the Buffered input
	 static int _CurrentKeyState;	//the current key state being checked in the Buffered input (Up or Down) 

public:
	Input();
	~Input();

	//RECOMMEND: Do not call this function because game class will take care of this.
	static void Init(HINSTANCE hInstance, HWND hWnd);

	static void ProcessKeyBoardInformation();

	//return true while the user holds dow the key, such as auto fire
	static bool GetKey(int KeyCode);
	static bool GetKeyDown(int KeyCode);
	static bool GetKeyUp(int KeyCode);

	static void Release();

};