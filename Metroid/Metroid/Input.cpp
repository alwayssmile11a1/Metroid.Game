#include "Input.h"

LPDIRECTINPUT8 Input::_DirectInput;		// The DirectInput object         
LPDIRECTINPUTDEVICE8 Input::_Keyboard;	// The keyboard device 
BYTE Input::_KeyStates[256];			// DirectInput keyboard state buffer 									
DIDEVICEOBJECTDATA Input::_KeyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data
std::vector<int> Input::_KeyCodesVector;
std::vector<int> Input::_KeyStatesVector;

Input::Input()
{	
	// constructor is empty.
	// We don't initialize static data member here, 
	// because static data initialization will happen on every constructor call.
}

Input::~Input()
{

}

void Input::Release()
{
	if (_DirectInput != NULL)
	{
		_DirectInput->Release();
		_DirectInput = NULL;
	}
	if (_Keyboard != NULL)
	{
		_Keyboard->Unacquire();
		_Keyboard->Release();
		_Keyboard = NULL;
	}
}

void Input::Init(HINSTANCE hInstance, HWND hWnd)
{
	//Release first for sure
	Release();

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
		DISCL_FOREGROUND |		//The application requires foreground access. 
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

void Input::ProcessKeyBoardInformation()
{
	if (_Keyboard == NULL) return;

	HRESULT result;

	// Collect all key states first
	result = _Keyboard->GetDeviceState(sizeof(_KeyStates), _KeyStates);
	
	//if window lost focus, acquire 
	if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
	{
		_Keyboard->Acquire();
		return;
	}

	// Handle key press event
	// NOTES: Buffered input is like an Event
	// Collect all buffered events (also clear them from DirectInput buffer)
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	_Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	//insert keycodes and keystates into vectors
	_KeyCodesVector.insert(_KeyCodesVector.end(), &(_KeyEvents[0].dwOfs), &(_KeyEvents[0].dwOfs) + dwElements);
	_KeyStatesVector.insert(_KeyStatesVector.end(), &(_KeyEvents[0].dwData), &(_KeyEvents[0].dwData) + dwElements);

}

bool Input::GetKey(int keyCode)
{
	return (_KeyStates[keyCode] & 0x80) > 0;
}

bool Input::GetKeyDown(int keyCode) 
{
	//check if this keycode is pressed
	std::vector<int>::iterator it = std::find(_KeyCodesVector.begin(), _KeyCodesVector.end(), keyCode);
	bool keyCodePressed = (it != _KeyCodesVector.end());
	
	if (keyCodePressed)
	{
		//check if it is key down
		return (_KeyStatesVector.at(it - _KeyCodesVector.begin()) & 0x80) > 0;
	}
	else
	{
		return false;
	}

}

bool Input::GetKeyUp(int keyCode) 
{ 
	//check if this keycode is pressed
	std::vector<int>::iterator it = std::find(_KeyCodesVector.begin(), _KeyCodesVector.end(), keyCode);
	bool keyCodePressed = (it != _KeyCodesVector.end());

	if (keyCodePressed)
	{
		//check if it is key up
		return (_KeyStatesVector.at(it - _KeyCodesVector.begin()) & 0x80) <= 0;
	}
	else
	{
		return false;
	}
}

void Input::ClearBuffedInput()
{
	_KeyCodesVector.clear();
	_KeyStatesVector.clear();
}