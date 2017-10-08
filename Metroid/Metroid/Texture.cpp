#include "Texture.h"

Texture::Texture()
{
	//set
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Bounds = Vector2(0, 0);
	_RectPosition = Vector2(0, 0);
	_OriginBounds = Vector2(0, 0);
	_FilePath = NULL;
	D3ddev = NULL;
	_Image = NULL;
	_TextureHandler = NULL;
}

Texture::Texture(LPDIRECT3DDEVICE9 d3ddev, LPWSTR filePath)
{
	//set basic information
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_RectPosition = Vector2(0, 0);
	_FilePath = filePath;
	D3ddev = d3ddev;
	_Image = NULL;

	//_SpriteHandler
	HRESULT res = D3DXCreateSprite(d3ddev, &_TextureHandler);
	if (res != D3D_OK) return;
	_TextureHandler->GetDevice(&d3ddev);

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

Texture::Texture(LPDIRECT3DDEVICE9 d3ddev, LPWSTR filePath, float width, float height, float rectX, float rectY)
{
	//set
	_Transcolor = D3DCOLOR_XRGB(255, 255, 255);
	_Bounds = Vector2(width, height);
	_RectPosition = Vector2(rectX, rectY);
	_FilePath = filePath;
	D3ddev = d3ddev;
	_Image = NULL;

	//_SpriteHandler
	HRESULT res = D3DXCreateSprite(d3ddev, &_TextureHandler);
	if (res != D3D_OK) return;
	_TextureHandler->GetDevice(&d3ddev);

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

Texture::Texture(const Texture &texture)
{
	_Transcolor = texture._Transcolor;
	_Bounds = texture._Bounds;
	_RectPosition = texture._RectPosition;
	D3ddev = texture.D3ddev;
	_FilePath = texture._FilePath;

	//_SpriteHandler
	D3DXCreateSprite(D3ddev, &_TextureHandler);
	_TextureHandler->GetDevice(&D3ddev);

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

Texture& Texture::operator=(const Texture &texture)
{
	_Transcolor = texture._Transcolor;
	_Bounds = texture._Bounds;
	_RectPosition = texture._RectPosition;
	D3ddev = texture.D3ddev;
	_FilePath = texture._FilePath;

	//copy _Image and _SpriteHandler - actually we create a new one here
	//I don't really know the way to copy the content of _Image and _SpriteHandler to the other one
	_Image = NULL;
	//_SpriteHandler
	D3DXCreateSprite(D3ddev, &_TextureHandler);
	_TextureHandler->GetDevice(&D3ddev);

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
Vector2 Texture::GetBounds()
{
	return _Bounds;
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

void Texture::Render(float x, float y)
{
	if (_TextureHandler == NULL) return;

	//start render a sprite
	_TextureHandler->Begin(D3DXSPRITE_ALPHABLEND);

	//// Build our matrix to rotate, scale and position our sprite
	//D3DXMATRIX mat;

	//// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	//D3DXMatrixTransformation2D(&mat, NULL, 0.0, &_ScaleFactor, &_CenterPosition, _Rotation, &D3DXVECTOR2(x, y));

	//_TextureHandler->SetTransform(&mat);

	//the portion of image we want to draw
	RECT srect;
	srect.left = _RectPosition.GetX();
	srect.top = _RectPosition.GetY();
	srect.right = srect.left + _Bounds.GetX();
	srect.bottom = srect.top + _Bounds.GetY();

	//position to draw in our world
	D3DXVECTOR3 position(x, y, 0);

	//draw sprite
	_TextureHandler->Draw(
		_Image,
		&srect,
		NULL,
		&position,
		_Transcolor
	);

	//end of drawing
	_TextureHandler->End();
}

Texture::~Texture()
{
	if (_TextureHandler != NULL)
	{
		_TextureHandler->Release();
		_TextureHandler = NULL;
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
