#include "Texture.h"

Texture::Texture()
{
	//set
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Bounds.Set(0, 0);
	_RectPosition.Set(0, 0);
	_OriginBounds.Set(0, 0);
	_ScaleFactor.Set(0,0); 
	_OriginPosition.Set(0,0);
	_IsCenterOrigin = true;
	_Rotation = 0;
	_FilePath = NULL;
	_Image = NULL;
}

Texture::Texture(LPWSTR filePath)
{
	//set basic information
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_RectPosition.Set(0, 0);
	_FilePath = filePath;
	_ScaleFactor.Set(0, 0);
	_Rotation = 0;
	_Image = NULL;
	_IsCenterOrigin = true;

	//Get image from file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		return;
	}

	//set default bounds
	_Bounds.Set(info.Width, info.Height);
	_OriginBounds.Set(info.Width, info.Height);
	_OriginPosition.Set(info.Width/2, info.Height/2);

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

Texture::Texture(LPWSTR filePath, float width, float height, float rectX, float rectY, float scaleX, float scaleY)
{
	//set
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Bounds = Vector2(width, height);
	_RectPosition = Vector2(rectX, rectY);
	_ScaleFactor.Set(scaleX, scaleY);
	_IsCenterOrigin = true;
	_Rotation = 0;
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
	_OriginBounds = texture._OriginBounds;
	_ScaleFactor = texture._ScaleFactor;
	_Rotation = texture._Rotation;
	_OriginPosition = texture._OriginPosition;
	_IsCenterOrigin = texture._IsCenterOrigin;

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
	_OriginBounds = texture._OriginBounds;
	_ScaleFactor = texture._ScaleFactor;
	_Rotation = texture._Rotation;
	_OriginPosition = texture._OriginPosition;
	_IsCenterOrigin = texture._IsCenterOrigin;

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

Vector2 Texture::GetOriginPosition() const
{
	return _OriginPosition;
}
Vector2 Texture::GetScale() const
{
	return _ScaleFactor;
}

float Texture::GetRotation() const
{
	return _Rotation;
}

void Texture::SetOriginPosition(float centerX, float centerY)
{
	_OriginPosition.Set(centerX, centerY);
}
void Texture::SetRotation(float rotation)
{
	_Rotation = rotation;
}

void Texture::SetScale(float scaleX, float scaleY)
{
	_ScaleFactor.Set(scaleX, scaleY);
}

void Texture::SetCenterOrigin(bool center) 
{
	_IsCenterOrigin = center;
}
bool Texture::IsCenterOrigin() const
{
	return _IsCenterOrigin;
}

//Flip the image 
void Texture::Flip(bool flipX, bool flipY)
{
	if (flipX) _ScaleFactor.X *= -1;
	if (flipY) _ScaleFactor.Y *= -1;
}

Texture::~Texture()
{

	if (_Image != NULL)
	{
		_Image->Release();
		_Image = NULL;
	}
}
