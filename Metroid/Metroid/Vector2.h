// Vector2.h: a vector with two dimensions x and y
#pragma once

class Vector2
{
private:
	float x; //the width of the object
	float y; //the height of the object

public:
	//constructor and destructor
	Vector2();
	Vector2(float width, float height);
	~Vector2();

	//get and set
	float GetX();
	float GetY();
	void SetX(float x);
	void SetY(float y);

};

