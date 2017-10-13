#include "Sprite.h"

Sprite::Sprite()
{
	_Texture = NULL;
	_ScaleFactor.Set(1,1); 
	_RotationOrigin.Set(0,0); 
	_Rotation = 0;
	_Position.Set(0, 0);
	_IsCenterOrigin = true;
	_RectSize.Set(0,0); 
	_RectPosition.Set(0,0); 
	_Size.Set(0, 0);
}

Sprite::Sprite(Texture *texture) 
{
	_Texture = texture;
	_ScaleFactor.Set(1, 1);
	_RotationOrigin.Set(0, 0);
	_Rotation = 0;
	_Position.Set(0, 0);
	_IsCenterOrigin = true;
	_RectSize.Set(texture->GetImageSize().X, texture->GetImageSize().Y);
	_Size.Set(_RectSize.X, _RectSize.Y);
	_RectPosition.Set(0, 0);
}

Sprite::Sprite(Texture *texture, float x, float y, float rectLeft, float rectTop, float rectWidth, float rectHeight, float width, float height)
{
	//set
	_Texture = texture;
	_ScaleFactor.Set(width / rectWidth, height / rectHeight);
	_Size.Set(width, height);
	_RotationOrigin.Set(0, 0);
	_Position.Set(x, y);
	_IsCenterOrigin = true;
	_Rotation = 0;
	_RectSize.Set(rectWidth, rectHeight);
	_RectPosition.Set(rectLeft, rectTop);
}

Sprite::Sprite(const Sprite &sprite)
{
	//set
	_Texture = sprite._Texture;
	_ScaleFactor = sprite._ScaleFactor;
	_Size = sprite._Size;
	_RotationOrigin = sprite._RotationOrigin;
	_IsCenterOrigin = sprite._IsCenterOrigin;
	_Rotation = sprite._Rotation;
	_Position = sprite._Position;
	_RectSize = sprite._RectSize;
	_RectPosition = sprite._RectPosition;
}

Sprite& Sprite::operator=(const Sprite &sprite)
{
	//set
	_Texture = sprite._Texture;
	_Size = sprite._Size;
	_ScaleFactor = sprite._ScaleFactor;
	_RotationOrigin = sprite._RotationOrigin;
	_IsCenterOrigin = sprite._IsCenterOrigin;
	_Rotation = sprite._Rotation;
	_Position = sprite._Position;
	_RectSize = sprite._RectSize;
	_RectPosition = sprite._RectPosition;

	return *this;
}

//all get functions
Vector2 Sprite::GetRotationOrigin() const
{
	return _RotationOrigin;
}
float Sprite::GetRotation() const
{
	return _Rotation;
}
Vector2 Sprite::GetScale() const
{
	return _ScaleFactor;
}

Texture*  Sprite::GetTexture() const
{
	return _Texture;
}

Vector2 Sprite::GetSize() const
{
	return _Size;
}

//all set functions
void Sprite::SetRotationOrigin(float centerX, float centerY)
{
	_RotationOrigin.Set(centerX, centerY);
}
void Sprite::SetRotation(float rotation)
{
	_Rotation = rotation;
}

Vector2 Sprite::GetPosition() const
{
	return _Position;
}

Vector2 Sprite::GetRectSize() const
{
	return _RectSize;
}
Vector2 Sprite::GetRectPosition() const
{
	return _RectPosition;
}

void Sprite::SetPosition(float x, float y)
{
	_Position.Set(x, y);
}

void  Sprite::SetTexture(Texture &texture)
{
	_Texture = &texture;
}

void Sprite::SetSize(float width, float height)
{
	_Size.Set(width, height);
	_ScaleFactor.Set(width /_RectSize.X, height / _RectSize.Y);
}

void Sprite::SetCenterRotationOrigin(bool center)
{
	_IsCenterOrigin = center;
}

bool Sprite::IsCenterOrigin() const
{
	return _IsCenterOrigin;
}

void Sprite::SetRectPosition(float rectX, float rectY)
{
	_RectPosition.Set(rectX, rectY);
}
void Sprite::SetRectSize(float rectWidth, float rectHeight)
{
	_RectSize.Set(rectWidth, rectHeight);
}

//Flip the image 
void Sprite::Flip(bool flipX, bool flipY)
{
	if (flipX) _ScaleFactor.X *= -1;
	if (flipY) _ScaleFactor.Y *= -1;
}

void Sprite::ResetToWhole()
{
	_RectSize.Set(_Texture->GetImageSize().X, _Texture->GetImageSize().Y);
	_ScaleFactor.Set(1, 1);
}

Sprite::~Sprite()
{

}
