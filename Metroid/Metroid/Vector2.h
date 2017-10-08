// Vector2.h: a vector with two dimensions x and y
// a small note is that in C++, class is by default value type
#pragma once

class Vector2
{
public:

	float X;
	float Y;

	//constructor and destructor
	Vector2();
	Vector2(float width, float height);
	Vector2(const Vector2&vector);
	~Vector2();
	

	//get and set
	void Set(float x, float y);

	//Overloading methods
	Vector2& operator+(const Vector2 &b);
	Vector2& operator-(const Vector2 &b);
	Vector2& operator=(const Vector2 &b);
	bool operator==(const Vector2 &b);

};

