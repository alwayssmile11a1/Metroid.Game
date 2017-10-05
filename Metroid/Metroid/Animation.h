#pragma once

#include "stdafx.h"
#include "Sprite.h"
class Animation
{
public:
	LPDIRECT3DTEXTURE9 _Image; //usually a spriteSheet image containing many sprites 
	Sprite _CurrentSprite; 
	int _Index;						// Current sprite index
	int _Width;								// Sprite width
	int _Height;							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row
	LPCWSTR _FilePath;
public:
	Animation();
	Animation(LPDIRECT3DDEVICE9 d3ddev, LPCWSTR FilePath, int Width, int Height, int Count, int SpritePerRow);
	void Next();
	void Reset();

	// Render current sprite at location (X,Y) at the target surface
	void Render(int X, int Y);
	

	~Animation();
};

