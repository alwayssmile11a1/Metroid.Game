#include "TextureRegion.h"

TextureRegion::TextureRegion()
{
	//set
	_RectPosition.Set(0, 0);
	_RectSize.Set(0, 0);
	_Texture = NULL;
}


TextureRegion::TextureRegion(Texture *texture, float rectX, float rectY, float rectWidth, float rectHeight)
{
	//set
	_Texture = texture;
	_RectSize = Vector2(rectWidth, rectHeight);
	_RectPosition = Vector2(rectX, rectY);
}

TextureRegion::TextureRegion(const TextureRegion &textureRegion)
{
	_RectPosition = textureRegion._RectPosition;
	_RectSize = textureRegion._RectSize;
	_Texture = textureRegion._Texture;

}

TextureRegion& TextureRegion::operator=(const TextureRegion &textureRegion)
{
	_RectPosition = textureRegion._RectPosition;
	_RectSize = textureRegion._RectSize;
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

Texture* TextureRegion::GetTexture() const
{
	return _Texture;
}

TextureRegion::~TextureRegion()
{

}
