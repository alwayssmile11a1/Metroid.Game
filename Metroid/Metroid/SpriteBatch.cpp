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

	if (_SpriteHandler == NULL) return;

	//position to draw in our world
	_Position.x = x;
	_Position.y = y;
	_Position.z = 0;

	//draw sprite
	_SpriteHandler->Draw(
		texture.GetImage(),
		NULL,
		NULL,
		&_Position,
		texture.GetTranscolor()
	);

}

void SpriteBatch::Draw(const Texture &texture, float x, float y, float width, float height)
{
	if (_SpriteHandler == NULL) return;

	//get scale factor
	_ScaleFactor.x = width/_RectSize.x;
	_ScaleFactor.y = height/_RectSize.y;

	//get scale origin position
	_ScaleOrigin.x = x;
	_ScaleOrigin.y = y;

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	//D3DXMatrixTransformation2D(&_Matrix, NULL, 0, &_ScaleFactor, &_CenterPosition, _RotationFactor, NULL);
	D3DXMatrixTransformation2D(&_Matrix, &_ScaleOrigin, 0, &_ScaleFactor, NULL, 0, NULL);

	_SpriteHandler->SetTransform(&_Matrix);

	//position to draw in our world
	_Position.x = x;
	_Position.y = y;
	_Position.z = 0;

	//draw sprite
	_SpriteHandler->Draw(
		texture.GetImage(),
		NULL,
		NULL,
		&_Position,
		texture.GetTranscolor()
	);

}

void SpriteBatch::Draw(const Sprite &sprite)
{
	if(_SpriteHandler == NULL) return;
	
	//get Position
	//position to draw in our world
	_Position.x = sprite.GetPosition().X;
	_Position.y = sprite.GetPosition().Y;
	_Position.z = 0;

	//get rect size
	_RectSize.x = sprite.GetRectSize().X;
	_RectSize.y = sprite.GetRectSize().Y;

	//get scale factor
	_ScaleFactor.x = sprite.GetScale().X;
	_ScaleFactor.y = sprite.GetScale().Y;

	//get center position
	_ScaleOrigin.x = _Position.x;
	_ScaleOrigin.y = _Position.y;

	//get rotation origin
	if (sprite.IsCenterOrigin())
	{
		_RotationOrigin.x = _RectSize.x / 2 + _Position.x;
		_RotationOrigin.x = _RectSize.y / 2 + _Position.y;
	}
	else
	{
		_RotationOrigin.x = sprite.GetRotationOrigin().X;
		_RotationOrigin.y = sprite.GetRotationOrigin().Y;
	}


	//get rotation
	_RotationFactor = sprite.GetRotation();

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	//D3DXMatrixTransformation2D(&_Matrix, NULL, 0, &_ScaleFactor, &_CenterPosition, _RotationFactor, NULL);
	D3DXMatrixTransformation2D(&_Matrix, &_ScaleOrigin, 0, &_ScaleFactor, &_RotationOrigin, _RotationFactor* Pi /180, NULL);
	
	_SpriteHandler->SetTransform(&_Matrix);
	
	//the portion of image we want to draw
	_Rect.left = sprite.GetRectPosition().X;
	_Rect.top = sprite.GetRectPosition().Y;
	_Rect.right = _Rect.left + _RectSize.x;
	_Rect.bottom = _Rect.top + _RectSize.y;

	_Center.x = _RectSize.x / 2;
	_Center.y = _RectSize.y / 2;
	_Center.z = 0;
	//draw sprite
	_SpriteHandler->Draw(
		sprite.GetTexture()->GetImage(),
		&_Rect,
		&_Center,
		&_Position,
		sprite.GetTexture()->GetTranscolor()
	);
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
