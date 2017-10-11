#include "SpriteBatch.h"

SpriteBatch::SpriteBatch()
{
	_SpriteHandler = NULL; //handle to a sprite 
	_Camera = NULL;
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
	_Camera = NULL;
}

void SpriteBatch::Release()
{
	if (_SpriteHandler != NULL)
	{
		_SpriteHandler->Release();
		_SpriteHandler = NULL;
	}

}

//Set the camera to be used by this batch
void SpriteBatch::SetCamera(Camera *camera)
{
	_Camera = camera;
}

void  SpriteBatch::GetActualPosition(D3DXVECTOR3 * postion, Camera *cam)
{
	if (cam == NULL) return;

	//get the actual postion
	D3DXMatrixIdentity(&_CameraMatrix);
	_CameraMatrix._22 = -1;
	_CameraMatrix._41 = -cam->GetPosition().X;
	_CameraMatrix._42 = +cam->GetPosition().Y;

	D3DXVec3Transform(&_ActualPosition, postion, &_CameraMatrix);
	postion->x = _ActualPosition.x;
	postion->y = _ActualPosition.y;
	postion->z = 0;
}

void SpriteBatch::Draw(const Texture &texture, float x, float y)
{

	if (_SpriteHandler == NULL || &texture ==NULL) return;

	//get virtual position
	_Position.x = x;
	_Position.y = y;
	_Position.z = 0;

	GetActualPosition(&_Position, _Camera);


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
	if (_SpriteHandler == NULL || &texture == NULL) return;

	//get virtual position
	_Position.x = x;
	_Position.y = y;
	_Position.z = 0;

	GetActualPosition(&_Position, _Camera);

	//get scale factor
	_ScaleFactor.x = width/_RectSize.x;
	_ScaleFactor.y = height/_RectSize.y;

	//get scale origin position
	_ScaleOrigin.x = x;
	_ScaleOrigin.y = y;

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	//D3DXMatrixTransformation2D(&_Matrix, NULL, 0, &_ScaleFactor, &_CenterPosition, _RotationFactor, NULL);
	D3DXMatrixTransformation2D(&_SpriteMatrix, &_ScaleOrigin, 0, &_ScaleFactor, NULL, 0, NULL);

	_SpriteHandler->SetTransform(&_SpriteMatrix);

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
	if(_SpriteHandler == NULL || &sprite == NULL) return;

	//virtual position
	_Position.x = sprite.GetPosition().X;
	_Position.y = sprite.GetPosition().Y;
	_Position.z = 0;

	GetActualPosition(&_Position, _Camera);

	//get rect size
	_RectSize.x = sprite.GetRectSize().X;
	_RectSize.y = sprite.GetRectSize().Y;

	//get scale factor
	_ScaleFactor.x = sprite.GetScale().X;
	_ScaleFactor.y = sprite.GetScale().Y;

	//get scale origin
	_ScaleOrigin.x = _Position.x;
	_ScaleOrigin.y = _Position.y;

	//get rotation origin
	if (sprite.IsCenterOrigin())
	{
		_RotationOrigin.x = _RectSize.x / 2 + _Position.x;
		_RotationOrigin.y = _RectSize.y / 2 + _Position.y;
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
	D3DXMatrixTransformation2D(&_SpriteMatrix, &_ScaleOrigin, 0, &_ScaleFactor, &_RotationOrigin, _RotationFactor* Pi /180, NULL);
	
	_SpriteHandler->SetTransform(&_SpriteMatrix);
	

	//the portion of image we want to draw
	_Rect.left = sprite.GetRectPosition().X;
	_Rect.top = sprite.GetRectPosition().Y;
	_Rect.right = _Rect.left + _RectSize.x;
	_Rect.bottom = _Rect.top + _RectSize.y;

	//Get center
	_Center.x = _RectSize.x/2;
	_Center.y = _RectSize.y/2;
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
