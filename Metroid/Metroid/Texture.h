//this class really needs to improve later
#pragma once

#include "stdafx.h"
#include "DirectXDevice.h"

//draw an image at specified position or draw a portion of image 
class Texture
{
protected:
	LPDIRECT3DTEXTURE9 _Image; //store the image that was loaded from file
	LPWSTR _FilePath;
	D3DCOLOR _Transcolor; //what color is needed to be transparent?
	Vector2 _ImageSize; //the whole width and height of the image
	Vector2 _RectSize; //the width and height of the rectangle portion in the image
	Vector2 _RectPosition; //the top left position of portion we want to draw

public:
	Texture();
	Texture(LPWSTR filePath);

	//create a texture from file
	Texture(LPWSTR filePath, float rectLeft, float rectTop, float rectWidth, float rectHeight);
	Texture(const Texture &texture);
	~Texture();

	Texture& operator=(const Texture &texture);

	//all get functions
	Vector2 GetRectSize() const;
	Vector2 GetRectPosition() const;
	D3DCOLOR GetTranscolor() const;
	LPDIRECT3DTEXTURE9 GetImage() const;

	//all set functions
	void SetRectPosition(float rectX, float rectY);
	void SetRectSize(float rectWidth, float rectHeight);
	void SetTranscolor(D3DCOLOR transcolor);
	void ResetToWhole();


};

