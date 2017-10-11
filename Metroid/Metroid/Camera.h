#pragma once

#include "stdafx.h"

//
class Camera
{
private:
	Vector2 _Position; //The camera position
	//Vector2 _Size; //the size of this camera

public:
	
	Camera();
	Camera(float x, float y);
	~Camera();

	Vector2 GetPosition();
	void SetPostion(float x, float y);
	void Update();


};