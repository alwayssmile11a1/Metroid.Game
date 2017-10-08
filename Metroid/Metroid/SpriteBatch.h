#pragma once

#include "stdafx.h"

//Manage drawing things
//Drawing must be called between the begin and end methods
//RECOMMEND: Consider using only one sprite batch throughout whole game
//And SpriteBatch is not automatically released, you have to call the release method yourself
class SpriteBatch
{
public:
	LPD3DXSPRITE _SpriteHandler; //handle to a sprite 

	LPDIRECT3DDEVICE9 D3ddev;

public:
	SpriteBatch();
	SpriteBatch(LPDIRECT3DDEVICE9 d3ddev);
	~SpriteBatch();
	//Release this batch
	void Release();
	void Begin();
	void End();
};

