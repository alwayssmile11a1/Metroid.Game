// Object.h: parent class of any game object
#pragma once
#include"stdafx.h"
#include "Texture.h"
class Object
{
private:
	Vector2 _Bounds; //the width and height of this object
	Vector2 _Velocity; //the vx and vy of this object
	Vector2 _Position; //the x, y coordinate of this object

	//hold the reference to a texture that has been created. 
	//Note that we don't allocate a new memory to this pointer (and you shouldn't)
	Texture *_Texture;
public:

	//constructor and destructor
	Object();
	Object(float x, float y, float width, float height);
	Object(const Object &object);
	~Object();

	Object& operator=(const Object &object);

	//All get functions
	Vector2 GetBounds();
	Vector2 GetVelocity();
	Vector2 GetPosition();
	Texture* GetTexture();

	//All set functions
	void SetBounds(const Vector2 &value);
	void SetVelocity(const Vector2 &value);
	void SetPosition(const Vector2 &value);
	void SetTexture(Texture *texture);

	//Update object
	void Update(DWORD dt);
};

