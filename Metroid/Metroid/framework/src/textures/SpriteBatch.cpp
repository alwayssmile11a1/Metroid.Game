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
	HRESULT res = D3DXCreateSprite(d3ddevice, &_SpriteHandler);
	if (res != D3D_OK) return;
	_SpriteHandler->GetDevice(&d3ddevice);
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
	_CameraMatrix._41 = -(cam->GetPosition().x - screenWidth / 2.0);
	_CameraMatrix._42 = +cam->GetPosition().y + screenHeight / 2.0;

	D3DXVec3Transform(&_ActualPosition, postion, &_CameraMatrix);
	postion->x = _ActualPosition.x;
	postion->y = _ActualPosition.y;
	postion->z = 0;
}

void SpriteBatch::Draw(const Texture &texture, float x, float y)
{

	if (_SpriteHandler == NULL || &texture == NULL) return;

	//get virtual position
	_Position.x = x;
	_Position.y = y;
	_Position.z = 0;

	GetActualPosition(&_Position, _Camera);

	//get scale origin
	_ScaleOrigin.x = _Position.x;
	_ScaleOrigin.y = _Position.y;

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&_SpriteMatrix, &_ScaleOrigin, 0, NULL, NULL, 0, NULL);

	_SpriteHandler->SetTransform(&_SpriteMatrix);

	//Get center
	_Center.x = texture.GetImageSize().x / 2;
	_Center.y = texture.GetImageSize().y / 2;
	_Center.z = 0;

	//draw sprite
	_SpriteHandler->Draw(
		texture.GetImage(),
		NULL,
		&_Center,
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
	_ScaleFactor.x = width / _RectSize.x;
	_ScaleFactor.y = height / _RectSize.y;

	//get scale origin
	_ScaleOrigin.x = _Position.x;
	_ScaleOrigin.y = _Position.y;

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&_SpriteMatrix, &_ScaleOrigin, 0, &_ScaleFactor, NULL, 0, NULL);

	_SpriteHandler->SetTransform(&_SpriteMatrix);


	//Get center
	_Center.x = texture.GetImageSize().x / 2;
	_Center.y = texture.GetImageSize().y / 2;
	_Center.z = 0;

	//draw sprite
	_SpriteHandler->Draw(
		texture.GetImage(),
		NULL,
		&_Center,
		&_Position,
		texture.GetTranscolor()
	);

}

//Draw textureregion at (x,y)
void SpriteBatch::Draw(const TextureRegion &textureRegion, float x, float y)
{
	if (_SpriteHandler == NULL || &textureRegion == NULL) return;

	//virtual position
	_Position.x = x;
	_Position.y = y;
	_Position.z = 0;

	GetActualPosition(&_Position, _Camera);

	//get rect size
	_RectSize.x = textureRegion.GetRectSize().x;
	_RectSize.y = textureRegion.GetRectSize().y;

	//get scale factor
	_ScaleFactor.x = textureRegion.GetScale().x;
	_ScaleFactor.y = textureRegion.GetScale().y;

	//get scale origin
	_ScaleOrigin.x = _Position.x;
	_ScaleOrigin.y = _Position.y;

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&_SpriteMatrix, &_ScaleOrigin, 0, &_ScaleFactor, NULL, 0, NULL);

	_SpriteHandler->SetTransform(&_SpriteMatrix);


	//the portion of image we want to draw
	_Rect.left = textureRegion.GetRectPosition().x;
	_Rect.top = textureRegion.GetRectPosition().y;
	_Rect.right = _Rect.left + _RectSize.x;
	_Rect.bottom = _Rect.top + _RectSize.y;

	//Get center
	_Center.x = _RectSize.x / 2;
	_Center.y = _RectSize.y / 2;
	_Center.z = 0;


	//draw sprite
	_SpriteHandler->Draw(
		textureRegion.GetTexture()->GetImage(),
		&_Rect,
		&_Center,
		&_Position,
		textureRegion.GetTexture()->GetTranscolor()
	);
}

//draw or portion of texture at (x,y) and stretch it to width and height
void SpriteBatch::Draw(const Texture &texture, float x, float y, float rectLeft, float rectTop, float rectWidth, float rectHeight, float width, float height)
{
	if (_SpriteHandler == NULL || &texture == NULL) return;

	//virtual position
	_Position.x = x;
	_Position.y = y;
	_Position.z = 0;

	GetActualPosition(&_Position, _Camera);

	//get rect size
	_RectSize.x = rectWidth;
	_RectSize.y = rectHeight;

	//get scale factor
	_ScaleFactor.x = width / _RectSize.x;
	_ScaleFactor.y = height / _RectSize.y;

	//get scale origin
	_ScaleOrigin.x = _Position.x;
	_ScaleOrigin.y = _Position.y;

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&_SpriteMatrix, &_ScaleOrigin, 0, &_ScaleFactor, NULL, 0, NULL);

	_SpriteHandler->SetTransform(&_SpriteMatrix);


	//the portion of image we want to draw
	_Rect.left = rectLeft;
	_Rect.top = rectTop;
	_Rect.right = _Rect.left + _RectSize.x;
	_Rect.bottom = _Rect.top + _RectSize.y;

	//Get center
	_Center.x = _RectSize.x / 2;
	_Center.y = _RectSize.y / 2;
	_Center.z = 0;


	//draw sprite
	_SpriteHandler->Draw(
		texture.GetImage(),
		&_Rect,
		&_Center,
		&_Position,
		texture.GetTranscolor()
	);
}

void SpriteBatch::Draw(const Sprite &sprite)
{
	if (_SpriteHandler == NULL || sprite.GetTexture() == NULL) return;

	//virtual position
	_Position.x = sprite.GetPosition().x;
	_Position.y = sprite.GetPosition().y;
	_Position.z = 0;

	GetActualPosition(&_Position, _Camera);

	//get rect size
	_RectSize.x = sprite.GetRectSize().x;
	_RectSize.y = sprite.GetRectSize().y;

	//get scale factor
	_ScaleFactor.x = sprite.GetScale().x;
	_ScaleFactor.y = sprite.GetScale().y;

	//get scale origin
	_ScaleOrigin.x = _Position.x;
	_ScaleOrigin.y = _Position.y;

	//get rotation origin
	if (sprite.IsCenterOrigin())
	{
		_RotationOrigin.x = _Position.x;
		_RotationOrigin.y = _Position.y;
	}
	else
	{
		_RotationOrigin.x = sprite.GetRotationOrigin().x;
		_RotationOrigin.y = sprite.GetRotationOrigin().y;
	}


	//get rotation
	_RotationFactor = sprite.GetRotation();

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&_SpriteMatrix, &_ScaleOrigin, 0, &_ScaleFactor, &_RotationOrigin, _RotationFactor* Pi / 180, NULL);

	_SpriteHandler->SetTransform(&_SpriteMatrix);


	//the portion of image we want to draw
	_Rect.left = sprite.GetRectPosition().x;
	_Rect.top = sprite.GetRectPosition().y;
	_Rect.right = _Rect.left + _RectSize.x;
	_Rect.bottom = _Rect.top + _RectSize.y;

	//Get center
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
