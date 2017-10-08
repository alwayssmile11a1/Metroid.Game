#pragma once

#include "stdafx.h"
#include "DirectXDevice.h"
#include "Texture.h"
#include "Sprite.h"

#define Pi 3.14159265

//Manage drawing things
//Drawing must be called between the begin and end methods
//RECOMMEND: Consider using only one sprite batch throughout whole game
//And SpriteBatch is not automatically released, you have to call the release method yourself
class SpriteBatch
{
private:
	LPD3DXSPRITE _SpriteHandler; //handle to a sprite 
	
	D3DXMATRIX _Matrix; // Build our matrix to rotate, scale and position our sprite
	RECT _Rect; //the portion of image we want to draw
	D3DXVECTOR3 _Position; //position to draw in our world
	D3DXVECTOR2 _Bounds; //the sprite bounds
	D3DXVECTOR2 _ScaleFactor; //scale
	D3DXVECTOR2 _OriginPosition; //the position that will be used as origin for rotating
	D3DXVECTOR2 _CenterPosition; //the center position of a sprite (used for scaling)
	float _RotationFactor; //rotation

public:
	SpriteBatch();
	~SpriteBatch();

	//Create batch
	void Create();

	//Release this batch
	void Release();

	//Draw 
	void Draw(const Texture &texture, float x, float y);
	void Draw(const Sprite &sprite);

	//begin drawing
	void Begin();

	//end drawing
	void End();

};

