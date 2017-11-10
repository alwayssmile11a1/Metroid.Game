#ifndef COLLISION_H
#define COLLISION_H

#include "Body.h"

#include "..\src\others\stdafx.h"

class Collision
{
private:
	// Kết quả của thuật toán kiểm tra va chạm,
	// không có va chạm sẽ trả về 1, 
	float _CollisionRatio;

	// Kết quả của va chạm tác động đến object,
	// dùng đề xác định hướng va chạm của các object (trên dưới trái phải)
	Vector2 _CollisionDirection;

	// Thời gian còn lại trong 1 frame sau khi va chạm xảy ra 
	// (thời gian của 1 frame > thời điểm va chạm - thời điểm bắt đầu frame)
	float _RemainingTime;

	Vector2 _CollisionPosition; // Vị trí của vật di chuyển khi va chạm với vật đứng yên

	float tempvx, tempvy; //velocity của vật a khi xem vật b đang đứng yên(nếu thực sự vật b đang di chuyển)
	float dxentry, dyentry, dxexit, dyexit; //dx entry / exit, dy entry / exit, khoảng d cần cần vật a đụng độ/ thoát ra khỏi vật b đứng yên (delta d của vật a trong khoảng delta_time)
	float deltadx, deltady; //khoảng delta vật a đi được trong khoảng thời gian delta_time
	float rxentry, rxexit, ryentry, ryexit; 
	float rentry;  //khoảng thời gian cần để thực sự xảy ra đụng độ
	float rexit; 	//khoảng thời gian cần để vật a thực sự thoát khỏi vật b



private: //private function
	

	// Hàm dùng để dự đoán vùng bao phủ của object trong frame kế
	bool IsOverlayingBroadphaseRect(Body &targetBody, Body &otherBody, float DeltaTime);

	void UpdateTargetPosition(Body &body, Vector2 move);


	void Push(Body &body);
	void Slide(Body &body);
	void Deflect(Body &body);

public:
	Collision();
	~Collision();

	bool PerformCollision(Body &targetBody, Body &otherBody, float DeltaTime, int collisionAction, bool &moveX, bool &moveY);

	bool IsColliding(Body &targetBody, Body &otherBody, float DeltaTime);
	
	// 2 body có chồng lên nhau hay không
	bool IsOverlaying(Body &targetBody, Body &otherBody, float& moveX, float& moveY);
};

#endif