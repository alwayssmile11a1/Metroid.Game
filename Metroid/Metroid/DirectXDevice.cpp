#include"DirectXDevice.h"


//Direct3D variables
LPDIRECT3DDEVICE9 DirectXDevice::D3Ddevice;
LPDIRECT3D9 DirectXDevice::D3D;

DirectXDevice::DirectXDevice()
{
	// constructor is empty.
	// We don't initialize static data member here, 
	// because static data initialization will happen on every constructor call.
}
DirectXDevice::~DirectXDevice()
{

}

int DirectXDevice::Init(HWND & hWnd, bool isFullScreen, int screenWidth, int _screenHeight)
{
	//Release first for sure
	Release();

	//initialize Direct3D
	D3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (D3D == NULL) {
		MessageBox(hWnd, L"Error initializing Direct3D", L"Error", MB_OK);
		return false;
	}

	//set DIRECT3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (isFullScreen)
	{
		d3dpp.Windowed = false; //full screen or not?
	}
	else
	{
		d3dpp.Windowed = true;
	}
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = screenWidth;
	d3dpp.BackBufferHeight = _screenHeight;
	d3dpp.hDeviceWindow = hWnd;

	//create Direct3D device
	D3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&D3Ddevice
	);

	if (D3Ddevice == NULL) {
		MessageBox(hWnd, L"Error creating Direct3D device", L"Error", MB_OK);
		return false;
	}

	return true;

}
void DirectXDevice::Release()
{
	//release the Direct3D device
	if (D3Ddevice != NULL) {
		D3Ddevice->Release();
		D3Ddevice = NULL;
	}

	//release the Direct3D object
	if (D3D != NULL)
	{
		D3D->Release();
		D3D = NULL;
	}

}