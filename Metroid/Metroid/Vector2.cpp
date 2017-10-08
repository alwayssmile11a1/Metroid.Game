#include"Vector2.h"

Vector2::Vector2()
{
	this->X = 0;
	this->Y = 0;
}


Vector2::Vector2(float x, float y)
{
	this->X = x;
	this->Y = y;
}

Vector2::Vector2(const Vector2 &vector)
{
	this->X = vector.X;
	this->Y = vector.Y;
}

Vector2::~Vector2()
{

}

void Vector2::Set(float x, float y)
{
	this->X = x;
	this->Y = y;
}


//Overloading
Vector2& Vector2::operator+(const Vector2 &b)
{
	Vector2 result;
	result.X = this->X + b.X;
	result.Y = this->Y + b.Y;
	return result;
}
Vector2& Vector2:: operator-(const Vector2 &b)
{
	Vector2 result;
	result.X = this->X - b.X;
	result.Y = this->Y - b.Y;
	return result;
}

Vector2&  Vector2::operator=(const Vector2 &b)
{
	this->X = b.X;
	this->Y = b.Y;
	return *this;
}

bool Vector2::operator==(const Vector2 &b)
{
	return (this->X == b.X) && (this->Y == b.Y);
}
