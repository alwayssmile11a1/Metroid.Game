#pragma once

#include "stdafx.h"

class Sprite
{
public:
	LPDIRECT3DTEXTURE9 _Image;
	LPD3DXSPRITE _SpriteHandler;
	D3DCOLOR _transcolor;

	float _Width;								// Sprite width
	float _Height;							// Sprite height
public:
	Sprite();
	Sprite(LPDIRECT3DDEVICE9 d3ddev, LPCWSTR FilePath, float Width, float Height, D3DCOLOR transcolor);

	//all get functions
	float getWidth();
	float getHeight();

	//all set functions
	void setWidth();
	void setHeight();

	// Render current sprite at location (X,Y) at the target surface
	void Render(int X, int Y, int rectX, int rectY);

	~Sprite();
};

