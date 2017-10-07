#pragma once
#include "stdafx.h"

#define KEY_DOWN(code) ( IsKeyDown(code) )

#define KEYBOARD_BUFFER_SIZE	1024

class Input
{
private:
	HWND _HWnd; //Handle of the Game Window

	LPDIRECTINPUT8       _DirectInput;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 
	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 

	// Buffered keyboard data
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];

	int _CurrentKeyCode;	//the current key code being checked in the Buffered input
	int _CurrentKeyState;	//the current key state being checked in the Buffered input (Up or Down) 

public:
	Input();
	Input(HINSTANCE hInstance, HWND hWnd);
	~Input();

	void ProcessKeyBoardInformation();

	//return true while the user holds dow the key, such as auto fire
	bool GetKey(int KeyCode);
	bool GetKeyDown(int KeyCode);
	bool GetKeyUp(int KeyCode);

};