#pragma once

#include "stdafx.h"
#include "DirectXDevice.h"
#include "Texture.h"
#include "Sprite.h"

//Manage drawing things
//Drawing must be called between the begin and end methods
//RECOMMEND: Consider using only one sprite batch throughout whole game
//And SpriteBatch is not automatically released, you have to call the release method yourself
class SpriteBatch
{
private:
	LPD3DXSPRITE _SpriteHandler; //handle to a sprite 

	//the portion of image we want to draw
	RECT _Rect;

	//position to draw in our world
	D3DXVECTOR3 _Position;

public:
	SpriteBatch();
	~SpriteBatch();

	//Create batch
	void Create();

	//Release this batch
	void Release();

	//Draw 
	void Draw(const Texture &texture, float x, float y);
	void Draw(const Sprite &sprite, float x, float y);

	//begin drawing
	void Begin();

	//end drawing
	void End();

};

