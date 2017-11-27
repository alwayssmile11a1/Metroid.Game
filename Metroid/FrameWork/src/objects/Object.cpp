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
	return mainBody;
}

void  Object::SetBody(Body *body)
{
	mainBody = body;
}

void  Object::SetBodyPosition(float x, float y)
{
	mainBody->SetPosition(x, y);
}
void  Object::SetVelocity(float vx, float vy)
{
	mainBody->SetVelocity(vx, vy);
}
void  Object::SetBodySize(float width, float height)
{
	mainBody->SetSize(width, height);
}

const Vector2& Object::GetVelocity() const
{
	return mainBody->GetVelocity();
}

void Object::SetMass(float mass)
{
	mainBody->SetMass(mass);
}


float Object::GetMass() const
{
	return mainBody->GetMass();
}


void Object::FitBody()
{
	mainBody->SetPosition(GetPosition().x, GetPosition().y);
	mainBody->SetSize(GetSize().x, GetSize().y);
}
