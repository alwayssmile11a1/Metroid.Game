#pragma once
#include "Sprite.h"
#include "Object.h"
#include "stdafx.h"

class Collision
{
private:
	// Kết quả của thuật toán kiểm tra va chạm,
	// không có va chạm sẽ trả về 1, 
	// có va chạm sẽ trả về khoảng thời gian cần để xảy ra va chạm (do delta time luôn nhỏ hơn 1)
	float _CollisionTime; 

	// Kết quả của va chạm tác động đến object,
	// dùng đề xác định hướng va chạm của các object (trên dưới trái phải)
	Vector2 _CollisionDirection; 

	// Thời gian còn lại trong 1 frame sau khi va chạm xảy ra 
	// (thời gian của 1 frame > thời điểm va chạm - thời điểm bắt đầu frame)
	float _RemainingTime; 

	Vector2 _CollisionPosition; // Vị trí của vật di chuyển khi va chạm với vật đứng yên

	float _dxEntry, _dyEntry, _dxExit, _dyExit;
	float _txEntry, _tyEntry, _txExit, _tyExit;

public:
	Collision();
	~Collision();

	void isCollide(Sprite* targetObjectSprite, Sprite* otherObjectSprite, float dt, DWORD DeltaTime);
	RECT getSweptBroadphaseRect(Sprite* object, float dt);
	bool isColliding(Sprite* targetObjectSprite, Sprite* otherObjectSprite, float& moveX, float& moveY, float dt);
	bool isColliding(RECT targetObjectRect, RECT otherObjectRect);
	bool checkCollision(Sprite* targetObjectSprite, Sprite* otherObjectSprite, float dt);
};

