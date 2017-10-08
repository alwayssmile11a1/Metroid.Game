//this class really needs to improve later
#pragma once

#include "stdafx.h"
#include "DirectXDevice.h"

//draw an image at specified position or draw a portion of image 
class Texture
{
public:
	LPDIRECT3DTEXTURE9 _Image; //store the image that was loaded from file

	LPWSTR _FilePath;

	D3DCOLOR _Transcolor; //what color is needed to be transparent?
	Vector2 _Bounds; //the width and height of this sprite
	Vector2 _RectPosition; //the top left position of portion we want to draw
	Vector2 _OriginBounds; //the whole bounds of the image

	D3DXVECTOR2 _ScaleFactor; //
	D3DXVECTOR2 _CenterPosition; //
	float _Rotation;

public:
	Texture();
	Texture(LPWSTR filePath);
	Texture(LPWSTR filePath, float width, float height, float rectX, float rectY);
	Texture(const Texture &texture);
	~Texture();

	Texture& operator=(const Texture &texture);

	//all get functions
	Vector2 GetBounds() const;
	LPDIRECT3DTEXTURE9 GetImage() const;
	Vector2 GetRectPosition() const;
	D3DCOLOR GetTranscolor() const;

	//all set functions
	void SetBounds(float width, float height);
	void SetTranscolor(D3DCOLOR transcolor);
	void SetRectPosition(float rectX, float rectY);

	void ResetToOriginBounds();

	// Render current sprite 
	//void Render(float x, float y);

};

