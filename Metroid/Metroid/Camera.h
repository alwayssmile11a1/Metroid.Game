#pragma once

#include "stdafx.h"

//
class Camera
{
private:
	Vector2 _Position; //The camera position
	Vector2 _Size; //the size of this camera
	Vector2 _ScaleFactor; 

public:
	
	Camera();
	Camera(float x, float y, float sizeX, float sizeY);
	~Camera();

	Vector2 GetPosition();
	Vector2 GetSize();
	Vector2 GetScaleFactor();

	//Set position
	void SetPosition(float x, float y);

	//Note that if the size of screen is different from the size of camera, consider using resize method
	void SetSize(float x, float y);

	//Resize 
	void Resize(float x, float y);


};