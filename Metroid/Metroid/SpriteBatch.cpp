#include "SpriteBatch.h"

SpriteBatch::SpriteBatch()
{
	D3ddev = NULL;
	_SpriteHandler = NULL;
}

SpriteBatch::SpriteBatch(LPDIRECT3DDEVICE9 d3ddev)
{
	D3ddev = d3ddev;

	//_SpriteHandler
	HRESULT res = D3DXCreateSprite(d3ddev, &_SpriteHandler);
	if (res != D3D_OK) return;
	_SpriteHandler->GetDevice(&d3ddev);
	
}



SpriteBatch::~SpriteBatch()
{
	//we do not release anything here
	//why? because we want SpriteBatch can be reference
	//so if we release things here, this spriteBatch can not be reference anymore
}

void SpriteBatch::Release()
{
	if (_SpriteHandler != NULL)
	{
		_SpriteHandler->Release();
		_SpriteHandler = NULL;
	}

	if (D3ddev != NULL)
	{
		D3ddev->Release();
		D3ddev = NULL;
	}
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
