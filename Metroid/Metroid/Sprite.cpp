#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddev, LPCWSTR FilePath, float Width, float Height, D3DCOLOR transcolor)
{
	D3DXIMAGE_INFO info;
	
	HRESULT result = D3DXGetImageInfoFromFile(FilePath , &info);
	
	_Image = NULL;
	HRESULT res = D3DXCreateSprite(d3ddev, &_SpriteHandler);
	if (res != D3D_OK) return;

	_SpriteHandler->GetDevice(&d3ddev);

	_transcolor = transcolor;
	_Width = Width;
	_Height = Height;

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
		transcolor,
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		return;
	}
}


void Sprite::Render(int X, int Y, int rectX, int rectY)
{
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srect;

	srect.left = rectX;
	srect.top = rectY;
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;
	
	D3DXVECTOR3 position((float)X, (float)Y, 0);

	_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&position,
		_transcolor
	);

	_SpriteHandler->End();
}

//void Sprite::Next()
//{
//	_Index = (_Index + _Count - 1) % _Count;
//}
//
//void Sprite::Reset()
//{
//	_Index = 0;
//}

Sprite::~Sprite()
{
}
