#ifndef BODY_H
#define BODY_H

#include "..\src\others\stdafx.h"

class Body: public GameObject
{
public: 
    enum BodyType { Static, Kinematic, Dynamic };

private:
	Vector2 _Position;
	Vector2 _Size;
	Vector2 _Velocity;
	Vector2 _LinearDrag;
	Vector2 _TotalVelocity;
	float _Mass; //the mass of body
	
	BodyType _BodyType;
	
	std::string _ID; //The id of this body
	
	bool _IsSensor;

	GameObject* _Extra; //Extra information for this body
				 //can be anything
	
public:
	//The categoryBits flag can be thought of as the fixture saying 'I am a ...'
	//usually just one Bit
	//NOTE:the value should be the power of two, such as: 1,2,4,8,16 ( 0x0001, 0x0002, 0x0004, 0x0008, 0x0010)
	short categoryBits;

	//the maskBits is like saying 'I will collide with a ...'
	short maskBits;
	//The idea was acquired from: http://www.iforce2d.net/b2dtut/collision-filtering
public:

	Body();
	Body(float x, float y, float width, float height, float vx, float vy);
	~Body();

	void SetVelocity(float vx, float vy);
	void SetSize(float width, float height);
	void SetPosition(float x, float y);
	void SetMass(float mass);
	void SetBodyType(BodyType type);
	//from 0-> infinity
	void SetLinearDrag(float xDrag, float yDrag);
	void SetID(const std::string &id);

	const Vector2& GetVelocity() const;
	const Vector2& GetSize() const;
	const Vector2& GetPosition() const;
	const Vector2& GetTotalVelocity() const;
	float GetMass() const;
	Body::BodyType GetBodyType();
	const std::string& GetID() const;

	void CalculateActualVelocity(float dt, float gravity);
	void IsSensor(bool triggered);
	bool IsSensor() const;

	void PutExtra(GameObject* anything);
	GameObject* GetExtra();

	//Go to the next position
	//this function was done by multiplying its velocity and deltatime 
	void Next(float dt, bool moveX, bool moveY);
	
};

#endif