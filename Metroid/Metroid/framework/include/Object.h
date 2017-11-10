#ifndef OBJECT_H
#define OBJECT_H

#include "..\src\others\stdafx.h"
#include "Sprite.h"
#include "Body.h"
//a sprite class but having a body 
class Object: public Sprite
{
protected:
	Body* mainBody;

public:

	//constructor and destructor
	Object();
	Object(Texture *texture);
	Object(Texture *texture, float x, float y, float rectLeft, float rectTop, float rectWidth, float rectHeight);
	//Object(const Object &object);
	~Object();

	/*Object& operator=(const Object &object);
	Object& operator=(const Object &object);*/

	void SetBody(Body *body);
	void SetBodyPosition(float x, float y);
	void SetVelocity(float vx, float vy);
	void SetBodySize(float width, float height);
	void SetMass(float mass);

	const Vector2& GetVelocity() const;
	float GetMass() const;
	Body* GetBody();

	//Set the position and the size of the body equal sprite'
	void FitBody();

	void Update(float dt);
};

#endif