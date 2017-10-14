//this class really needs to improve later
#pragma once

#include "stdafx.h"
#include "Global.h"

//just like a image
class Texture
{
private:
	LPDIRECT3DTEXTURE9 _Image; //store the image that was loaded from file
	LPWSTR _FilePath;
	D3DCOLOR _Transcolor; //what color is needed to be transparent?
	Vector2 _ImageSize; //the whole width and height of the image

public:
	Texture();
	Texture(LPWSTR filePath);

	//create a texture from file
	Texture(const Texture &texture);
	~Texture();

	Texture& operator=(const Texture &texture);

	//all get functions
	D3DCOLOR GetTranscolor() const;
	LPDIRECT3DTEXTURE9 GetImage() const;
	Vector2 GetImageSize() const;

	//all set functions
	void SetTranscolor(D3DCOLOR transcolor);

};

