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
	//_CreateNewTexture = false;
}

Sprite::Sprite(Texture *texture/*, bool createNew*/) 
{
	/*_CreateNewTexture = createNew;

	if (createNew)
	{
		_Texture = new Texture();
		*_Texture = *texture;
	}
	else
	{
		_Texture = texture;
	}*/
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

Sprite::Sprite(Texture *texture, /*bool createNew,*/ float x, float y, float rectLeft, float rectTop, float rectWidth, float rectHeight, Vector2 Velocity, Vector2 Direction)
{
	/*_CreateNewTexture = createNew;

	if (createNew)
	{
		_Texture = new Texture();
		*_Texture = *texture;
	}
	else
	{
		_Texture = texture;
	}*/
	_Texture = texture;
	_ScaleFactor.Set(1, 1);
	_Size.Set(rectWidth, rectWidth);
	_RotationOrigin.Set(0, 0);
	_Position.Set(x, y);
	_IsCenterOrigin = true;
	_Rotation = 0;
	_RectSize.Set(rectWidth, rectHeight);
	_RectPosition.Set(rectLeft, rectTop);
	_Velocity = Velocity;
	_Direction = Direction;
}

Sprite::Sprite(const Sprite &sprite)
{
	////set
	//_CreateNewTexture = sprite._CreateNewTexture;

	//if (_CreateNewTexture)
	//{
	//	_Texture = new Texture();
	//	*_Texture = *sprite._Texture;
	//}
	//else
	//{
	//	_Texture = sprite._Texture;
	//}
	_Texture = sprite._Texture;
	_ScaleFactor = sprite._ScaleFactor;
	_Size = sprite._Size;
	_RotationOrigin = sprite._RotationOrigin;
	_IsCenterOrigin = sprite._IsCenterOrigin;
	_Rotation = sprite._Rotation;
	_Position = sprite._Position;
	_RectSize = sprite._RectSize;
	_RectPosition = sprite._RectPosition;
	_Velocity = sprite._Velocity;
	_Direction = sprite._Direction;
}

Sprite& Sprite::operator=(const Sprite &sprite)
{
	////set
	//_CreateNewTexture = sprite._CreateNewTexture;

	//if (_CreateNewTexture)
	//{
	//	_Texture = new Texture();
	//	*_Texture = *sprite._Texture;
	//}
	//else
	//{
	//	_Texture = sprite._Texture;
	//}
	_Texture = sprite._Texture;
	_Size = sprite._Size;
	_ScaleFactor = sprite._ScaleFactor;
	_RotationOrigin = sprite._RotationOrigin;
	_IsCenterOrigin = sprite._IsCenterOrigin;
	_Rotation = sprite._Rotation;
	_Position = sprite._Position;
	_RectSize = sprite._RectSize;
	_RectPosition = sprite._RectPosition;
	_Velocity = sprite._Velocity;
	_Direction = sprite._Direction;

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

Vector2 Sprite::GetVelocity() const
{
	return _Velocity;
}

Vector2 Sprite::GetDirection() const
{
	return _Direction;
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

void Sprite::SetDirection(Vector2 value)
{
	_Direction = value;
}

void Sprite::SetVelocity(Vector2 value)
{
	_Velocity = value;
}

void Sprite::SetRegion(TextureRegion *textureRegion)
{
	_Texture = textureRegion->GetTexture();
	_RectSize = textureRegion->GetRectSize(); 
	_RectPosition = textureRegion->GetRectPosition();
	_ScaleFactor.X = abs(_ScaleFactor.X)* textureRegion->GetScale().X;
	_ScaleFactor.Y = abs(_ScaleFactor.Y)* textureRegion->GetScale().Y;
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

void  Sprite::SetTexture(Texture *texture)
{
	_Texture = texture;
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

	/*if (_CreateNewTexture && _Texture!=NULL)
	{
		delete _Texture;
		_Texture = NULL;
	}*/
}
