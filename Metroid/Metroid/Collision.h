#pragma once
#include "Body.h"
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

	float tempvx, tempvy; //velocity của vật a khi xem vật b đang đứng yên(nếu thực sự vật b đang di chuyển)
	float dxentry, dyentry, dxexit, dyexit; //dx entry / exit, dy entry / exit, khoảng d cần cần vật a đụng độ/ thoát ra khỏi vật b đứng yên (delta d của vật a trong khoảng delta_time)
	float deltadx, deltady; //khoảng delta vật a đi được trong khoảng thời gian delta_time
	float xentry, xexit, yentry, yexit; //tỉ lệ giữa delta d và d entry, exit
	float txentry, txexit, tyentry, tyexit; //khoảng thời gian cần để xảy ra đụng độ/ thoát khỏi b của a trên trục x và y
	float tentry;  //khoảng thời gian cần để thực sự xảy ra đụng độ
	float texit; 	//khoảng thời gian cần để vật a thực sự thoát khỏi vật b

public:
	Collision();
	~Collision();

	void isCollide(Body &targetBody, Body &otherBody, float DeltaTime);

	// Hàm dùng để dự đoán vùng bao phủ của object trong frame kế
	RECT getSweptBroadphaseRect(Body &object, float DeltaTime);


	bool isColliding(Body &targetBody, Body &otherBody, float& moveX, float& moveY, float dt);

	// Hàm dùng để ktra RECT của 2 object có chồng nhau hay ko
	bool isColliding(RECT targetObjectRect, RECT otherObjectRect);

	bool checkCollision(Body &targetBody, Body &otherBody, float DeltaTime, int collisionAction);

	void updateTargetPosition(Body &body, Vector2 move);
	void Push(Body &body);
	void Slide(Body &body);
	void Deflect(Body &body);
};