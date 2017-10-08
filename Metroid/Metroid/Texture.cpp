#include "Texture.h"

Texture::Texture()
{
	//set
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Bounds = Vector2(0, 0);
	_RectPosition = Vector2(0, 0);
	_OriginBounds = Vector2(0, 0);
	_FilePath = NULL;
	_Image = NULL;
}

Texture::Texture(LPWSTR filePath)
{
	//set basic information
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_RectPosition = Vector2(0, 0);
	_FilePath = filePath;
	_Image = NULL;

	//Get image from file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		return;
	}

	//set default bounds
	_Bounds = Vector2(info.Width, info.Height);
	_OriginBounds = Vector2(info.Width, info.Height);

	result = D3DXCreateTextureFromFileEx(
		DirectXDevice::D3Ddevice,
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

Texture::Texture(LPWSTR filePath, float width, float height, float rectX, float rectY)
{
	//set
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Bounds = Vector2(width, height);
	_RectPosition = Vector2(rectX, rectY);
	_FilePath = filePath;
	_Image = NULL;

	//Get image from file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		DirectXDevice::D3Ddevice,
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

Texture::Texture(const Texture &texture)
{
	_Transcolor = texture._Transcolor;
	_Bounds = texture._Bounds;
	_RectPosition = texture._RectPosition;
	_FilePath = texture._FilePath;

	//Get image from file
	_Image = NULL;
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_FilePath, &info);
	D3DXCreateTextureFromFileEx(
		DirectXDevice::D3Ddevice,
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

Texture& Texture::operator=(const Texture &texture)
{
	_Transcolor = texture._Transcolor;
	_Bounds = texture._Bounds;
	_RectPosition = texture._RectPosition;
	_FilePath = texture._FilePath;

	//copy _Image and _SpriteHandler - actually we create a new one here
	//I don't really know the way to copy the content of _Image and _SpriteHandler to the other one
	_Image = NULL;

	//Get image from file
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(_FilePath, &info);
	D3DXCreateTextureFromFileEx(
		DirectXDevice::D3Ddevice,
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
Vector2 Texture::GetBounds() const
{
	return _Bounds;
}

Vector2 Texture::GetRectPosition() const
{
	return _RectPosition;
}

D3DCOLOR Texture::GetTranscolor() const
{
	return _Transcolor;
}

//all set functions
void Texture::SetBounds(float width, float height)
{
	_Bounds = Vector2(width, height);
}
void Texture::SetTranscolor(D3DCOLOR transcolor)
{
	_Transcolor = transcolor;
}
void  Texture::SetRectPosition(float rectX, float rectY)
{
	_RectPosition = Vector2(rectX, rectY);
}

void Texture::ResetToOriginBounds()
{
	_Bounds = _OriginBounds;
}

LPDIRECT3DTEXTURE9 Texture::GetImage() const
{
	return _Image;
}

//void Texture::Render(float x, float y)
//{
//	//if (_TextureHandler == NULL) return;
//
//	//start render a sprite
//	//_TextureHandler->Begin(D3DXSPRITE_ALPHABLEND);
//
//	//// Build our matrix to rotate, scale and position our sprite
//	//D3DXMATRIX mat;
//
//	//// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
//	//D3DXMatrixTransformation2D(&mat, NULL, 0.0, &_ScaleFactor, &_CenterPosition, _Rotation, &D3DXVECTOR2(x, y));
//
//	//_TextureHandler->SetTransform(&mat);
//
//	//position to draw in our world
//	D3DXVECTOR3 position(x, y, 0);
//
//	//draw sprite
//	_TextureHandler->Draw(
//		_Image,
//		&srect,
//		NULL,
//		&position,
//		_Transcolor
//	);
//
//	//end of drawing
//	_TextureHandler->End();
//}

Texture::~Texture()
{

	if (_Image != NULL)
	{
		_Image->Release();
		_Image = NULL;
	}
}
