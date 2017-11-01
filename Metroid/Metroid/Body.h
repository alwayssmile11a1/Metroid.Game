#pragma once


#include "stdafx.h"


#define CenToPixel 37.795276

class Body
{
public: 
    enum BodyType { Dynamic, Kinematic, Static };

private:
	Vector2 _Position;
	Vector2 _Size;
	Vector2 _Velocity;
	Vector2 _LinearImpulse;
	Vector2 _TotalVelocity;
	float _Mass; //the mass of body
	
	BodyType _BodyType;
	
public:

	Body();
	Body(float x, float y, float width, float height, float vx, float vy);
	~Body();

	void SetVelocity(float vx, float vy);
	void SetSize(float width, float height);
	void SetPosition(float x, float y);
	void SetMass(float mass);
	void ApplyLinearImpulse(float xImpulse, float yImpulse);
	void SetBodyType(BodyType type);

	const Vector2& GetVelocity() const;
	const Vector2& GetSize() const;
	const Vector2& GetPosition() const;
	const Vector2& GetTotalVelocity(float dt);
	float GetMass() const;
	Body::BodyType GetBodyType();

	//Go to the next position
	//this function was done by multiplying its velocity and deltatime 
	void Next(float dt);

};

