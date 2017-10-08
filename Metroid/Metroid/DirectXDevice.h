#pragma once

#include "stdafx.h"

//DirectX device class. Not automatically released after creating
//if you init this class, even though by static function, consider calling release function.
class DirectXDevice
{
public:
	//Direct3D variables
	static LPDIRECT3D9 D3D;
	static LPDIRECT3DDEVICE9 D3Ddevice;


	DirectXDevice();
	~DirectXDevice();

	static int Init(HWND &_HWnd, bool isFullScreen, int _ScreenWidth, int _ScreenHeight);
	static void Release();

};