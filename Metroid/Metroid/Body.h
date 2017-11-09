#pragma once


#include "stdafx.h"
#include"Player.h"

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

	Player* _Extra; //Extra information for this body
				 //can be anything

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

	void PutExtra(Player* anything);
	Player* GetExtra();

	//Go to the next position
	//this function was done by multiplying its velocity and deltatime 
	void Next(float dt, bool moveX, bool moveY);
	
};

