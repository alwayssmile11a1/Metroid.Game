#include"Object.h"


Object::Object()
{
	
}

Object::Object(Texture *texture):Sprite(texture)
{

}

Object::Object(Texture *texture, float x, float y, float rectLeft, float rectTop, float rectWidth, float rectHeight)
	:Sprite(texture, x, y, rectLeft, rectTop, rectWidth, rectHeight)
{
	
}

//Object::Object(const Object &object)
//{
//	
//}


Object::~Object()
{
	
}

//Object& Object::operator=(const Object &object)
//{
//	
//	return *this;
//}

Body* Object::GetMainBody() 
{
	return _MainBody;
}

void  Object::SetMainBody(Body *body)
{
	_MainBody = body;
}

void  Object::SetBodyPosition(float x, float y)
{
	_MainBody->SetPosition(x, y);
}
void  Object::SetVelocity(float vx, float vy)
{
	_MainBody->SetVelocity(vx, vy);
}
void  Object::SetBodySize(float width, float height)
{
	_MainBody->SetSize(width, height);
}

const Vector2& Object::GetVelocity() const
{
	return _MainBody->GetVelocity();
}

void Object::SetMass(float mass)
{
	_MainBody->SetMass(mass);
}


float Object::GetMass() const
{
	return _MainBody->GetMass();
}


void Object::FitBody()
{
	_MainBody->SetPosition(GetPosition().x, GetPosition().y);
	_MainBody->SetSize(GetSize().x, GetSize().y);
}
