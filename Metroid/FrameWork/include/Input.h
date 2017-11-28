#ifndef INPUT_H
#define INPUT_H

#include "..\src\others\stdafx.h"
#include <algorithm>    // std::find
#define KEYBOARD_BUFFER_SIZE	1024

//Input class (Keyboard, mouse, etc)
//Not automatically released after init. Consider calling release function
class Input
{
private:
	HWND _HWnd;
	LPDIRECTINPUT8       _DirectInput;		// The DirectInput object     

	//Keyboard
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 
	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data
	std::vector<int> _KeyCodesVector; //a vector of keycodes contained in buffered input
	std::vector<int> _KeyStatesVector; //a vector of keystates contained in buffered input


	//Mouse
	LPDIRECTINPUTDEVICE8 _Mouse; // The mouse device
	DIMOUSESTATE  _MouseState; // DirectInput mouse state buffer 
	DIDEVICEOBJECTDATA _MouseEvents[16]; // Buffered keyboard data
	std::vector<int> _MouseCodesVector; //a vector of keycodes contained in buffered input
	std::vector<int> _MouseStatesVector; //a vector of keystates contained in buffered input
	Vector2 _MousePosition;

	bool InitKeyBoard();
	bool InitMouse();

public:
	Input();
	~Input();

	//RECOMMEND: Do not call this function because game class will take care of this.
	//If you do call this function, consider to release it first 
	void Init(HINSTANCE hInstance, HWND hWnd);

	//RECOMMEND: Do not call this function because game class will take care of this.
	void ProcessKeyBoardInformation();

	//RECOMMEND: Do not call this function because game class will take care of this.
	void ProcessMouseInformation();

	//clear buffed input. It means in the same frame after you call this function, getkeydown and getkeyup is disposed  
	//Note that this function just has its affect in the frame after you call it 
	void ClearBuffedInput();

	//return true while the user holds down the key, such as auto fire
	bool GetKey(int keyCode);

	//return true during the time user stars pressing the key until it reaches the very bottom of the key.  
	bool GetKeyDown(int keyCode);

	//return true during the time user stars releasing the key until it reaches the very top of the key.  
	bool GetKeyUp(int keyCode);

	//return true while the user holds dow the key, such as auto fire
	bool GetMouse(int mouse);

	//NOTE: weird action
	//return true during the time user stars pressing the key until it reaches the very bottom of the key.  
	bool GetMouseDown(int mouse);

	//NOTE: weird action
	//return true during the time user stars releasing the key until it reaches the very top of the key.  
	bool GetMouseUp(int mouse);

	//Get Mouse Position
	Vector2 GetMousePosition();

	void Release();

};

#endif