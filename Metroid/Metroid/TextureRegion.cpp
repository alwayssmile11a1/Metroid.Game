#include "TextureRegion.h"

TextureRegion::TextureRegion()
{
	//set
	_RectPosition.Set(0, 0);
	_RectSize.Set(0, 0);
	_Texture = NULL;
	_ScaleFactor.Set(1, 1);
	//_CreateNewTexture = false;
}


TextureRegion::TextureRegion(Texture *texture, /*bool createNew, */float rectX, float rectY, float rectWidth, float rectHeight)
{
	////set
	//_CreateNewTexture = createNew;

	//if (createNew)
	//{
	//	_Texture = new Texture();
	//	*_Texture = *texture;
	//}
	//else
	//{
	//	_Texture = texture;
	//}
	_Texture = texture;
	_RectSize = Vector2(rectWidth, rectHeight);
	_RectPosition = Vector2(rectX, rectY);
	_ScaleFactor.Set(1, 1);
}

TextureRegion::TextureRegion(const TextureRegion &textureRegion)
{
	_RectPosition = textureRegion._RectPosition;
	_RectSize = textureRegion._RectSize;
	_ScaleFactor = textureRegion._ScaleFactor;
	//set
	/*_CreateNewTexture = textureRegion._CreateNewTexture;

	if (_CreateNewTexture)
	{
		_Texture = new Texture();
		*_Texture = *textureRegion._Texture;
	}
	else
	{
		_Texture = textureRegion._Texture;
	}*/
	_Texture = textureRegion._Texture;
}

TextureRegion& TextureRegion::operator=(const TextureRegion &textureRegion)
{
	_RectPosition = textureRegion._RectPosition;
	_RectSize = textureRegion._RectSize;
	_ScaleFactor = textureRegion._ScaleFactor;
	////set
	//_CreateNewTexture = textureRegion._CreateNewTexture;

	//if (_CreateNewTexture)
	//{
	//	_Texture = new Texture();
	//	*_Texture = *textureRegion._Texture;
	//}
	//else
	//{
	//	_Texture = textureRegion._Texture;
	//}

	_Texture = textureRegion._Texture;
	return *this;
}

//all get functions
Vector2 TextureRegion::GetRectSize() const
{
	return _RectSize;
}

Vector2 TextureRegion::GetRectPosition() const
{
	return _RectPosition;
}

//all set functions
void  TextureRegion::SetRectPosition(float rectX, float rectY)
{
	_RectPosition = Vector2(rectX, rectY);
}

void TextureRegion::SetRectSize(float rectWidth, float rectHeight)
{
	_RectSize.Set(rectWidth, rectHeight);
}

void TextureRegion::SetTexture(Texture *Texture)
{
	_Texture = Texture;
}

Texture* TextureRegion::GetTexture() const
{
	return _Texture;
}

//Flip the image 
void TextureRegion::Flip(bool flipX, bool flipY)
{
	if (flipX) _ScaleFactor.x *= -1;
	if (flipY) _ScaleFactor.y *= -1;
}

Vector2 TextureRegion::GetScale() const
{
	return _ScaleFactor;
}

TextureRegion::~TextureRegion()
{
	/*if (_CreateNewTexture && _Texture != NULL)
	{
		delete _Texture;
		_Texture = NULL;
	}*/
}
