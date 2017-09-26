#include"Object.h"

Object::Object()
{
	bounds.setX(0);
	bounds.setY(0);
	velocity.setX(0);
	velocity.setY(0);
}

Object::Object(int width, int height)
{
	bounds.setX(width);
	bounds.setY(height);
	velocity.setX(0);
	velocity.setY(0);
}

Object::~Object()
{

}

//All get functions
Vector2 Object::getBounds()
{
	return bounds;
}

Vector2 Object::getVelocity()
{
	return velocity;
}

//All set functions
void Object::setBounds(Vector2 value)
{
	bounds = value;
}
void Object::setVelocity(Vector2 value)
{
	velocity = value;
}

void Object::update(DWORD dt)
{

}