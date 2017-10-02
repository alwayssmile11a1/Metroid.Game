#include "Sprite.h"



Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler, LPCWSTR FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	D3DXIMAGE_INFO info;
	
	HRESULT result = D3DXGetImageInfoFromFile(FilePath , &info);
	
	_Image = NULL;
	_SpriteHandler = SpriteHandler;

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	if (result != D3D_OK)
	{
		return;
	}


	/*result = D3DXGetImageInfoFromFile((LPWSTR)FilePath, &info);*/


	/*SpriteHandler->GetDevice(&d3ddev);*/

	result = D3DXCreateTextureFromFileEx(
		d3ddev,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 0, 0),
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		return;
	}
}

void Sprite::Render(int X, int Y)
{
	this->Render(NULL, X, Y);
}

void Sprite::Render(LPDIRECT3DSURFACE9 Target, int X, int Y)
{
	RECT srect;

	srect.left = (_Index % _SpritePerRow)*(_Width)+1;
	srect.top = (_Index / _SpritePerRow)*(_Height)+1;
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height + 1;

	D3DXVECTOR3 position((float)X, (float)Y, 0);

	_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void Sprite::Next()
{
	_Index = (_Index + _Count - 1) % _Count;
}

void Sprite::Reset()
{
	_Index = 0;
}

Sprite::~Sprite()
{
}
