#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddev, LPCWSTR filePath, float x, float y)
{
	//set basic information
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Position = Vector2(x, y);
	_RectPosition = Vector2(0, 0);
	_Image = NULL;
	
	//_SpriteHandler
	HRESULT res = D3DXCreateSprite(d3ddev, &_SpriteHandler);
	if (res != D3D_OK) return;
	_SpriteHandler->GetDevice(&d3ddev);

	//Get image from file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		return;
	}
	
	//set default bounds
	_Bounds = Vector2(info.Width, info.Height);

	result = D3DXCreateTextureFromFileEx(
		d3ddev,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		_Transcolor,
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		return;
	}
}

Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddev, LPCWSTR filePath, float x, float y, float width, float height, float rectX, float rectY)
{
	//set
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Bounds = Vector2(width, height);
	_RectPosition = Vector2(rectX, rectY);
	_Position = Vector2(x, y);
	_Image = NULL;

	//_SpriteHandler
	HRESULT res = D3DXCreateSprite(d3ddev, &_SpriteHandler);
	if (res != D3D_OK) return;
	_SpriteHandler->GetDevice(&d3ddev);

	//Get image from file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		d3ddev,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		_Transcolor,
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		return;
	}
}

//all get functions
Vector2 Sprite::GetPosition()
{
	return _Position;
}
Vector2 Sprite::GetBounds()
{
	return _Bounds;
}

//all set functions
void Sprite::SetBounds(float width, float height)
{
	_Bounds = Vector2(width, height);
}
void Sprite::SetPosition(int x, int y)
{
	_Position = Vector2(x, y);
}
void Sprite::SetTranscolor(D3DCOLOR transcolor)
{
	_Transcolor = transcolor;
}
void  Sprite::SetRectPosition(float rectX, float rectY)
{
	_RectPosition = Vector2(rectX, rectY);
}

void Sprite::Render()
{
	//start render a sprite
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	//the portion of image we want to draw
	RECT srect;
	srect.left = _RectPosition.GetX();
	srect.top = _RectPosition.GetY();
	srect.right = srect.left + _Bounds.GetX();
	srect.bottom = srect.top + _Bounds.GetY();
	
	//position to draw in our world
	D3DXVECTOR3 position((float)_Position.GetX(), (float)_Position.GetY(), 0);
	
	//draw sprite
	_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&position,
		_Transcolor
	);

	//end of drawing
	_SpriteHandler->End();
}

Sprite::~Sprite()
{
}
