#include"Vector2.h"

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}


Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2()
{

}

float Vector2::GetX()
{
	return x;
}
float Vector2::GetY()
{
	return y;
}
void Vector2::SetX(float x)
{
	this->x = x;
}
void Vector2::SetY(float y)
{
	this->y = y;
}
