#include "Sprite.h"

Sprite::Sprite()
{
	//set
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Bounds = Vector2(0,0);
	_RectPosition = Vector2(0, 0);
	_Position = Vector2(0, 0);
	_FilePath = NULL;
	D3ddev = NULL;
	_Image = NULL;
	_SpriteHandler = NULL;
}

Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddev, LPWSTR filePath, float x, float y)
{
	//set basic information
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Position = Vector2(x, y);
	_RectPosition = Vector2(0, 0);
	_FilePath = filePath;
	D3ddev = d3ddev;
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

Sprite::Sprite(LPDIRECT3DDEVICE9 d3ddev, LPWSTR filePath, float x, float y, float width, float height, float rectX, float rectY)
{
	//set
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Bounds = Vector2(width, height);
	_RectPosition = Vector2(rectX, rectY);
	_Position = Vector2(x, y);
	_FilePath = filePath;
	D3ddev = d3ddev;
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

Sprite::Sprite(const Sprite &sprite)
{
	_Transcolor = sprite._Transcolor;
	_Position = sprite._Position;
	_Bounds = sprite._Bounds;
	_RectPosition = sprite._RectPosition;
	D3ddev = sprite.D3ddev;
	_FilePath = sprite._FilePath;

	//_SpriteHandler
	D3DXCreateSprite(D3ddev, &_SpriteHandler);
	_SpriteHandler->GetDevice(&D3ddev);

	//Get image from file
	_Image = NULL;
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_FilePath, &info);
	D3DXCreateTextureFromFileEx(
		D3ddev,
		_FilePath,
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

}

Sprite& Sprite::operator=(const Sprite &sprite)
{
	_Transcolor = sprite._Transcolor;
	_Position = sprite._Position;
	_Bounds = sprite._Bounds;
	_RectPosition = sprite._RectPosition;
	D3ddev = sprite.D3ddev;
	_FilePath = sprite._FilePath;

	//copy _Image and _SpriteHandler - actually we create a new one here
	//I don't really know the way to copy the content of _Image and _SpriteHandler to the other one
	_Image = NULL;
	//_SpriteHandler
	D3DXCreateSprite(D3ddev, &_SpriteHandler);
	_SpriteHandler->GetDevice(&D3ddev);
	
	//Get image from file
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_FilePath, &info);
	D3DXCreateTextureFromFileEx(
		D3ddev,
		_FilePath,
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


	return *this;
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
	srect.left = _RectPosition.X;
	srect.top = _RectPosition.Y;
	srect.right = srect.left + _Bounds.X;
	srect.bottom = srect.top + _Bounds.Y;
	
	//position to draw in our world
	D3DXVECTOR3 position((float)_Position.X, (float)_Position.Y, 0);
	
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
	if (_SpriteHandler != NULL)
	{
		_SpriteHandler->Release();
		_SpriteHandler = NULL;
	}
	if (_Image != NULL)
	{
		_Image->Release();
		_Image = NULL;
	}
	if (D3ddev != NULL)
	{
		D3ddev->Release();
		D3ddev = NULL;
	}
}
