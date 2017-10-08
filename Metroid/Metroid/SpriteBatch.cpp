#include "SpriteBatch.h"

SpriteBatch::SpriteBatch()
{

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
	//the portion of image we want to draw
	_Rect.left = texture.GetRectPosition().GetX();
	_Rect.top = texture.GetRectPosition().GetY();
	_Rect.right = _Rect.left + texture.GetBounds().GetX();
	_Rect.bottom = _Rect.top + texture.GetBounds().GetY();

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

void SpriteBatch::Draw(const Sprite &sprite, float x, float y)
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
