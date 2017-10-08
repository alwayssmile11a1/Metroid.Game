#include "SpriteBatch.h"

SpriteBatch::SpriteBatch()
{
	_SpriteHandler = NULL; //handle to a sprite 

}


SpriteBatch::~SpriteBatch()
{
	//we do not release anything here
	//why? because we want SpriteBatch can be reference
	//so if we release things here, this spriteBatch can not be reference anymore
}

void SpriteBatch::Create()
{
	//_SpriteHandler
	HRESULT res = D3DXCreateSprite(DirectXDevice::D3Ddevice, &_SpriteHandler);
	if (res != D3D_OK) return;
	_SpriteHandler->GetDevice(&DirectXDevice::D3Ddevice);
}

void SpriteBatch::Release()
{
	if (_SpriteHandler != NULL)
	{
		_SpriteHandler->Release();
		_SpriteHandler = NULL;
	}

}

void SpriteBatch::Draw(const Texture &texture, float x, float y)
{
	if(_SpriteHandler == NULL) return;
	
	//get bounds
	_Bounds.x = texture.GetBounds().X;
	_Bounds.y = texture.GetBounds().Y;

	//get scale factor
	_ScaleFactor.x = texture.GetScale().X;
	_ScaleFactor.y = texture.GetScale().Y;

	//get center position
	_CenterPosition.x = x + _Bounds.x / 2;
	_CenterPosition.y = y + _Bounds.y / 2;

	if (texture.IsCenterOrigin())
	{
		_OriginPosition = _CenterPosition;
	}
	else
	{
		_OriginPosition.x = texture.GetOriginPosition().X;
		_OriginPosition.y = texture.GetOriginPosition().Y;
	}
	_RotationFactor = texture.GetRotation();

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	//D3DXMatrixTransformation2D(&_Matrix, NULL, 0, &_ScaleFactor, &_CenterPosition, _RotationFactor, NULL);
	D3DXMatrixTransformation2D(&_Matrix, &_CenterPosition, 0, &_ScaleFactor, &_OriginPosition, _RotationFactor* Pi /180, NULL);
	
	_SpriteHandler->SetTransform(&_Matrix);
	
	//the portion of image we want to draw
	_Rect.left = texture.GetRectPosition().X;
	_Rect.top = texture.GetRectPosition().Y;
	_Rect.right = _Rect.left + texture.GetBounds().X;
	_Rect.bottom = _Rect.top + texture.GetBounds().Y;

	//position to draw in our world
	_Position.x = x;
	_Position.y = y;
	_Position.z = 0;

	//draw sprite
	_SpriteHandler->Draw(
		texture.GetImage(),
		&_Rect,
		NULL,
		&_Position,
		texture.GetTranscolor()
	);

}

void SpriteBatch::Draw(const Sprite &sprite)
{

}


void SpriteBatch::Begin()
{
	//start render sprites
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
}
void SpriteBatch::End()
{
	//end of drawing
	_SpriteHandler->End();
}
