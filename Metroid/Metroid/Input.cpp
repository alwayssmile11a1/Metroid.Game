#include "Input.h"

Input::Input()
{	
	_HWnd = NULL;
	_DirectInput = NULL;		
	_Keyboard = NULL;	
}

Input::Input(HINSTANCE hInstance, HWND hWnd)
{
	_HWnd = hWnd;
	HRESULT
		result = DirectInput8Create
		(
			hInstance, //handle for a window instance
			DIRECTINPUT_VERSION, //direct input version
			IID_IDirectInput8, //
			(VOID**)&_DirectInput,  //receive the interface pointer
			NULL //NULL if the interface is not aggregated
		);

	// TO-DO: put in exception handling
	if (result != DI_OK) return;

	//trace(L"DirectInput has been created");

	result = _DirectInput->CreateDevice(
		GUID_SysKeyboard, //The default system keyboard
		&_Keyboard,  //receive the IDirectInputDevice8 interface pointer 
		NULL //NULL if the interface is not aggregated.
	);

	// TO-DO: put in exception handling
	if (result != DI_OK) return;

	//trace(L"DirectInput keyboard has been created");


	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.
	result = _Keyboard->SetDataFormat(&c_dfDIKeyboard);

	//trace(L"SetDataFormat for keyboard successfully");

	result = _Keyboard->SetCooperativeLevel(hWnd, 
		DISCL_FOREGROUND|		//The application requires foreground access. 
								//If foreground access is granted, 
								//the device is automatically unacquired when the associated window moves to the background.
		DISCL_NONEXCLUSIVE		//The application requires nonexclusive access. 
								//Access to the device does not interfere with other applications that are accessing the same device.
	);

	//trace(L"SetCooperativeLevel for keyboard successfully");

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	//trace(L"SetProperty for keyboard successfully");

	result = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (result != DI_OK) return;

	result = _Keyboard->Acquire();
	if (result != DI_OK) return;

	//trace(L"Keyboard has been acquired successfully");
}

Input::~Input()
{
	if(_DirectInput != NULL)
	{
		_DirectInput->Release();
		_DirectInput = NULL;
	}
	if (_Keyboard != NULL)
	{
		_Keyboard->Release();
		_Keyboard = NULL;
	}
}

void Input::ProcessKeyBoardInformation()
{
	// Collect all key states first
	_Keyboard->GetDeviceState(sizeof(_KeyStates), _KeyStates);

	// Handle key press event
	// NOTES: Buffered input is like an Event
	// Collect all buffered events (also clear them from DirectInput buffer)
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT result = _Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		_CurrentKeyCode = _KeyEvents[i].dwOfs;
		_CurrentKeyState = _KeyEvents[i].dwData;
		/*if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);*/
	}
}

bool Input::GetKey(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}

bool Input::GetKeyDown(int KeyCode) 
{
	return (_CurrentKeyCode == KeyCode && (_CurrentKeyState & 0x80) > 0);
}

bool Input::GetKeyUp(int KeyCode) 
{ 
	return (_CurrentKeyCode == KeyCode && (_CurrentKeyState & 0x80) <= 0);
}