#include"Camera.h"

Camera::Camera()
{
	_Position.Set(0, 0);
}
Camera::Camera(float x, float y)
{
	_Position.Set(x, y);
}

Camera::~Camera()
{

}

Vector2 Camera::GetPosition()
{
	return _Position;
}

void Camera::SetPostion(float x, float y)
{
	_Position.Set(x, y);
}

void Camera::Update()
{

}