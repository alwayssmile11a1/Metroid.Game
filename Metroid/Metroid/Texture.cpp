#include "Texture.h"

Texture::Texture()
{
	//set
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_ImageSize.Set(0, 0);
	_FilePath = NULL;
	_Image = NULL;
}

Texture::Texture(LPWSTR filePath)
{
	//set basic information
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_FilePath = filePath;
	_Image = NULL;

	//Get image from file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		return;
	}

	//set size
	_ImageSize.Set(info.Width, info.Height);

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
	_FilePath = texture._FilePath;
	_ImageSize = texture._ImageSize;

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
	_FilePath = texture._FilePath;
	_ImageSize = texture._ImageSize;

	//copy _Image
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
D3DCOLOR Texture::GetTranscolor() const
{
	return _Transcolor;
}

LPDIRECT3DTEXTURE9 Texture::GetImage() const
{
	return _Image;
}

//all set functions
void Texture::SetTranscolor(D3DCOLOR transcolor)
{
	_Transcolor = transcolor;
}

Vector2 Texture::GetImageSize() const
{
	return _ImageSize;
}

Texture::~Texture()
{

	if (_Image != NULL)
	{
		_Image->Release();
		_Image = NULL;
	}
}
