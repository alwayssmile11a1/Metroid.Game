#pragma once
#include "stdafx.h"
#include <algorithm>    // std::find
#define KEYBOARD_BUFFER_SIZE	1024

class Input
{
private:
	 static LPDIRECTINPUT8       _DirectInput;		// The DirectInput object         
	 static LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 
	 static BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 

	 static DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data
	
	 static std::vector<int> _KeyCodesVector; //a vector of keycodes contained in buffered input
	 static std::vector<int> _KeyStatesVector; //a vector of keystates contained in buffered input

public:
	Input();
	~Input();

	//RECOMMEND: Do not call this function because game class will take care of this.
	static void Init(HINSTANCE hInstance, HWND hWnd);

	//RECOMMEND: Do not call this function because game class will take care of this.
	static void ProcessKeyBoardInformation();

	//clear buffed input. It means in the same frame after you call this function, getkeydown and getkeyup is disposed  
	//Note that this function just has its affect in the frame after you call it 
	static void ClearBuffedInput();

	//return true while the user holds dow the key, such as auto fire
	static bool GetKey(int keyCode);

	//return true during the time user stars pressing the key until it reaches the very bottom of the key.  
	static bool GetKeyDown(int keyCode);

	//return true during the time user stars releasing the key until it reaches the very top of the key.  
	static bool GetKeyUp(int keyCode);

	static void Release();


};