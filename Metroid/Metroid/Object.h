// Object.h: parent class of any game object 
#pragma once
#include"stdafx.h"
#include "Sprite.h"
class Object
{
public:
	Vector2 size; //the width and height of this object
	Vector2 velocity; //the vx and vy of this object
	Vector2 position; //the x, y coordinate of this object

	/*LPD3DXSPRITE _SpriteHandler;*/

	float kitty_vx_last;  // last vx of kitty before stop ( to determine the direction of object)

	DWORD last_time;	 // this is to control the animate rate of object

	LPDIRECT3DSURFACE9 Background;
	Sprite * object_right;
	Sprite * object_left;
public:
	/*LPDIRECT3DSURFACE9 _Background;*/

	//constructor and destructor
	Object();
	Object(float width, float height, float x, float y);
	Object(const Object &object);
	~Object();

	//All get functions
	Vector2 getBounds();
	Vector2 getVelocity();
	Vector2 getPosition();

	//All set functions
	void setBounds(Vector2 value);
	void setVelocity(Vector2 value);
	void setPosition(Vector2 value);


	//Update object
	void update(DWORD dt);
	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 backbuffer, int Delta);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv, LPCWSTR Filename, LPCWSTR Filename_Left, LPCWSTR Filename_Right, LPDIRECT3DSURFACE9 _Background
	, int Sprite_Count, int Sprite_per_row, D3DCOLOR transcolor);
};

