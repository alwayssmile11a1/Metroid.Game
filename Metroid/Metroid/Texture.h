//this class really needs to improve later
#pragma once

#include "stdafx.h"
#include "DirectXDevice.h"

//draw an image at specified position or draw a portion of image 
class Texture
{
private:
	LPDIRECT3DTEXTURE9 _Image; //store the image that was loaded from file

	LPWSTR _FilePath;

	D3DCOLOR _Transcolor; //what color is needed to be transparent?
	Vector2 _Bounds; //the width and height of this sprite
	Vector2 _RectPosition; //the top left position of portion we want to draw
	Vector2 _OriginBounds; //the whole bounds of the image

	Vector2 _ScaleFactor; //scale
	Vector2 _OriginPosition; //the position that will be used as origin for rotating
	float _Rotation;

	float _IsCenterOrigin;

public:
	Texture();
	Texture(LPWSTR filePath);
	Texture(LPWSTR filePath, float width, float height, float rectX, float rectY, float scaleX, float scaleY);
	Texture(const Texture &texture);
	~Texture();

	Texture& operator=(const Texture &texture);

	//all get functions
	Vector2 GetBounds() const;
	Vector2 GetRectPosition() const;
	Vector2 GetOriginPosition() const;
	Vector2 GetScale() const;
	float GetRotation() const;
	D3DCOLOR GetTranscolor() const;
	LPDIRECT3DTEXTURE9 GetImage() const;

	//all set functions
	void SetBounds(float width, float height);
	void SetRectPosition(float rectX, float rectY);
	void SetOriginPosition(float centerX, float centerY);
	void SetRotation(float rotation);
	void SetScale(float scaleX, float scaleY);
	void SetTranscolor(D3DCOLOR transcolor);
	void ResetToOriginBounds();

	//if true, set the origin of this sprite to be always in the center of this texture
	void SetCenterOrigin(bool center); 
	bool IsCenterOrigin() const;

};

