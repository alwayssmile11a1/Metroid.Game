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
	/*void Next();
	void Reset();*/

	// Render current sprite at location (X,Y) at the target surface
	//void Render(int X, int Y);
	void Render(int X, int Y);

	~Sprite();
};

