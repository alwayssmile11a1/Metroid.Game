#include "Sprite.h"

Sprite::Sprite()
{
	_ScaleFactor.Set(1,1); 
	_RotationOrigin.Set(0,0); 
	_Rotation = 0;
	_Position.Set(0, 0);
	_IsCenterOrigin = true;
}

Sprite::Sprite(LPWSTR filePath) :Texture(filePath)
{
	_ScaleFactor.Set(1, 1);
	_RotationOrigin.Set(0, 0);
	_Rotation = 0;
	_Position.Set(0, 0);
	_IsCenterOrigin = true;
}

Sprite::Sprite(LPWSTR filePath, float x, float y, float rectLeft, float rectTop, float rectWidth, float rectHeight, float width, float height)
	:Texture(filePath, rectLeft, rectTop, rectWidth, rectHeight)
{
	//set
	_ScaleFactor.Set(width / rectWidth, height / rectHeight);
	_RotationOrigin.Set(0, 0);
	_Position.Set(x, y);
	_IsCenterOrigin = true;
	_Rotation = 0;

}

Sprite::Sprite(const Sprite &sprite) :Texture(sprite)
{
	//set
	_ScaleFactor = sprite._ScaleFactor;
	_RotationOrigin = sprite._RotationOrigin;
	_IsCenterOrigin = sprite._IsCenterOrigin;
	_Rotation = sprite._Rotation;
	_Position = sprite._Position;
}

Sprite& Sprite::operator=(const Sprite &sprite)
{
	Texture::operator=(sprite);
	//set
	_ScaleFactor = sprite._ScaleFactor;
	_RotationOrigin = sprite._RotationOrigin;
	_IsCenterOrigin = sprite._IsCenterOrigin;
	_Rotation = sprite._Rotation;
	_Position = sprite._Position;

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

void Sprite::SetPosition(float x, float y)
{
	_Position.Set(x, y);
}


void Sprite::SetSize(float width, float height)
{
	_ScaleFactor.Set(width / _RectSize.X, height / _RectSize.Y);
}

void Sprite::SetCenterRotationOrigin(bool center)
{
	_IsCenterOrigin = center;
}

bool Sprite::IsCenterOrigin() const
{
	return _IsCenterOrigin;
}

//Flip the image 
void Sprite::Flip(bool flipX, bool flipY)
{
	if (flipX) _ScaleFactor.X *= -1;
	if (flipY) _ScaleFactor.Y *= -1;
}

void Sprite::ResetToWhole()
{
	Texture::ResetToWhole();
	_ScaleFactor.Set(1, 1);
}

Sprite::~Sprite()
{

}
