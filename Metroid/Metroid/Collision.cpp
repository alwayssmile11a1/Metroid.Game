﻿#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::isCollide(Body &targetBody, Body &otherBody, float DeltaTime)
{
	// sử dụng Broadphase rect để kt vùng tiếp theo có va chạm ko
	RECT broadphaseRect = getSweptBroadphaseRect(targetBody, DeltaTime);
	RECT otherBodyRect;
	otherBodyRect.top = otherBody.GetPosition().y + otherBody.GetSize().y / 2;
	otherBodyRect.bottom = otherBody.GetPosition().y - otherBody.GetSize().y / 2;
	otherBodyRect.left = otherBody.GetPosition().x - otherBody.GetSize().x / 2;
	otherBodyRect.right = otherBody.GetPosition().x + otherBody.GetSize().x / 2;

	if (!isColliding(broadphaseRect, otherBodyRect)) {
		_CollisionDirection.x = 0.0f;
		_CollisionDirection.y = 0.0f;
		_CollisionTime = 1.0f;
		_RemainingTime = std::numeric_limits<float>::infinity();
		_CollisionPosition.x = 0.0f;
		_CollisionPosition.y = 0.0f;
		return;
	}

	Vector2 targetVelocity = targetBody.GetTotalVelocity(DeltaTime);
	Vector2 otherVelocity = otherBody.GetTotalVelocity(DeltaTime);

	//tính toán dx entry và dx exit, có 2 trường hợp là vật a di chuyển ngược và xuôi với trục toạ độ
	tempvx = targetVelocity.x;
	tempvy = targetVelocity.y;
	if (otherVelocity.x != 0 && otherVelocity.y != 0) {
		tempvx = otherVelocity.x - targetVelocity.x;
		tempvy = otherVelocity.y - targetVelocity.y;
	}

	if (tempvx > 0.0f)
	{
		dxentry = (otherBody.GetPosition().x - otherBody.GetSize().x / 2) - (targetBody.GetPosition().x + targetBody.GetSize().x / 2);
		dxexit = (otherBody.GetPosition().x + otherBody.GetSize().x / 2) - (targetBody.GetPosition().x - targetBody.GetSize().x / 2);
	}
	else
	{
		dxentry = (otherBody.GetPosition().x + otherBody.GetSize().x / 2) - (targetBody.GetPosition().x - targetBody.GetSize().x / 2);
		dxexit = (otherBody.GetPosition().x - otherBody.GetSize().x / 2) - (targetBody.GetPosition().x + targetBody.GetSize().x / 2);
	}

	//tính toán dy entry và exit, tương tự với dx entry/ exit
	if (tempvy > 0.0f)
	{
		dyentry = (otherBody.GetPosition().y - otherBody.GetSize().y / 2) - (targetBody.GetPosition().y + targetBody.GetSize().y / 2);
		dyexit = (otherBody.GetPosition().y + otherBody.GetSize().y / 2) - (targetBody.GetPosition().y - targetBody.GetSize().y / 2);
	}
	else
	{
		dyentry = (otherBody.GetPosition().y + otherBody.GetSize().y / 2) - (targetBody.GetPosition().y - targetBody.GetSize().y / 2);
		dyexit = (otherBody.GetPosition().y - otherBody.GetSize().y / 2) - (targetBody.GetPosition().y + targetBody.GetSize().y / 2);
	}

	//tính toán t x entry/ exit
	if (targetVelocity.x == 0.0f) //tránh trường hợp a.velocity = 0 dẫn tới việc chia cho 0, nên ta gán x entry/ exit = +/-vô cùng
	{
		txentry = -std::numeric_limits<float>::infinity();
		txexit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txentry = dxentry / (tempvx * DeltaTime);
		txexit = dxexit / (tempvx * DeltaTime);
	}

	//tính toán t y entry/ exit, tương tự x entry/ exit
	if (targetVelocity.y == 0.0f)
	{
		tyentry = -std::numeric_limits<float>::infinity();
		tyexit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyentry = dyentry / (targetVelocity.y * DeltaTime);
		tyexit = dyexit / (targetVelocity.y * DeltaTime);
	}

	// tính toán thời gian va chạm và thoát khỏi thực sự của vật a chuyển động đối với vật b đứng yên
	tentry = max(txentry, tyentry);
	texit = min(txexit, tyexit);

	//sau khi tính toán được thời gian thực sự va chạm và thoát khỏi, ta kiểm tra xem việc va chạm có xảy ra hay không
	if ((tentry > texit) || //trường hợp không xảy ra va chạm 1: thời gian thực sự xảy ra va chạm > thời gian thực sự a thoát khỏi b

		(txentry < 0.0f && tyentry < 0.0f) || //trường hợp không xảy ra va chạm thứ 2: vật a có vận tốc = 0 dẫn đến x entry/ y entry = -vô cùng, hoặc vật a di chuyển hướng ra khỏi vật b

		(txentry > 1.0f) || (tyentry > 1.0f)) //trường hợp không xảy ra va chạm thứ 3: trong khoảng thời gian delta_time đang xét (thời gian của 1 frame) thì vật a di chuyển chưa tới vật b
	{
		_CollisionDirection.x = 0.0f;
		_CollisionDirection.y = 0.0f;
		_CollisionTime = 1.0f;
		_RemainingTime = std::numeric_limits<float>::infinity();
		_CollisionPosition.x = 0.0f;
		_CollisionPosition.y = 0.0f;
	}
	else //xảy ra va chạm, chia làm 4 trường hợp, tương ứng với 4 hướng va chạm của vật a so với vật b
	{
		if (txentry > tyentry)//nếu việc xảy ra va chạm nằm trên trục x 
		{
			if (dxentry < 0.0f)//nếu vật a nằm bên phải vật b => vật a va chạm cạnh bên phải của hình bao vật b
			{
				_CollisionDirection.x = abs(targetVelocity.x);
				_CollisionDirection.y = 0.0f;
			}
			else //nếu vật a nằm bên trái vật b => vật a va chạm cạnh bên trái của hình bao vật b
			{
				_CollisionDirection.x = -abs(targetVelocity.x);
				_CollisionDirection.y = 0.0f;
			}
		}
		else//nếu việc xảy ra va chạm nằm trên trục y
		{
			if (dyentry < 0.0f)//nếu vật a nằm bên dưới vật b => vật a sẽ va chạm cạnh dưới hình bao vât b
			{
				_CollisionDirection.x = 0.0f;
				_CollisionDirection.y = -abs(targetVelocity.y);
			}
			else//nếu vật a nằm bên trên vật b => vật a sẽ va chạm cạnh trên hình bao vât b
			{
				_CollisionDirection.x = 0.0f;
				_CollisionDirection.y = abs(targetVelocity.y);
			}
		}

		_CollisionTime = tentry;
		_RemainingTime = DeltaTime - tentry;
		_CollisionPosition.x = targetBody.GetPosition().x + tentry * tempvx;
		_CollisionPosition.y = targetBody.GetPosition().y + tentry * tempvy;
	}
}

RECT Collision::getSweptBroadphaseRect(Body &body, float DeltaTime)
{
	// vận tốc mỗi frame
	Vector2 velocity = Vector2(body.GetTotalVelocity(DeltaTime).x * DeltaTime, body.GetTotalVelocity(DeltaTime).y * DeltaTime);

	RECT rect;
	rect.top = velocity.y > 0 ? (body.GetPosition().y + body.GetSize().y / 2) + velocity.y : body.GetPosition().y + body.GetSize().y / 2;
	rect.bottom = velocity.y > 0 ? body.GetPosition().y - body.GetSize().y / 2 : body.GetPosition().y - body.GetSize().y / 2 + velocity.y;
	rect.left = velocity.x > 0 ? body.GetPosition().x - body.GetSize().x / 2 : body.GetPosition().x - body.GetSize().x / 2 + velocity.x;
	rect.right = velocity.x > 0 ? body.GetPosition().x + body.GetSize().x / 2 + velocity.x : body.GetPosition().x + body.GetSize().x / 2;

	return rect;
}

bool Collision::isColliding(Body &targetBody, Body &otherBody, float& moveX, float& moveY, float dt)
{
	moveX = moveY = 0.0f;
	//auto myRect = _target->getBounding();
	//auto otherRect = otherObject->getBounding();

	float left = otherBody.GetPosition().x - otherBody.GetSize().x / 2 - (targetBody.GetPosition().x + targetBody.GetSize().x / 2);
	float top = otherBody.GetPosition().y + otherBody.GetSize().y / 2 - (targetBody.GetPosition().y - targetBody.GetSize().y / 2);
	float right = otherBody.GetPosition().x + otherBody.GetSize().x / 2 - (targetBody.GetPosition().x - targetBody.GetSize().x / 2);
	float bottom = otherBody.GetPosition().y - otherBody.GetSize().y / 2 - (targetBody.GetPosition().y + targetBody.GetSize().y / 2);

	// kt coi có va chạm không
	//  CÓ va chạm khi 
	//  left < 0 && right > 0 && top > 0 && bottom < 0
	//
	if (left >= 0 || right <= 0 || top <= 0 || bottom >= 0)
		return false;

	// tính offset x, y để đi hết va chạm
	// lấy khoảng cách nhỏ nhất
	moveX = abs(left) < right ? left : right;
	moveY = top < abs(bottom) ? top : bottom;

	// chỉ lấy phần lấn vào nhỏ nhất
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

bool Collision::isColliding(RECT targetBodyRect, RECT otherBodyRect)
{
	return!(
		targetBodyRect.right < otherBodyRect.left ||
		targetBodyRect.left > otherBodyRect.right ||
		targetBodyRect.bottom > otherBodyRect.top ||
		targetBodyRect.top < otherBodyRect.bottom);
}

bool Collision::checkCollision(Body &targetBody, Body &otherBody, float DeltaTime, int collisionAction)
{
	Vector2 targetVelocity = targetBody.GetTotalVelocity(DeltaTime);
	Vector2 otherVelocity = otherBody.GetTotalVelocity(DeltaTime);

	isCollide(targetBody, otherBody, DeltaTime);

	if (_CollisionTime < 1.0f)
	{
		if (_CollisionDirection != Vector2(0, 0))
		{
			if (_CollisionDirection.x == targetVelocity.x * -1)
			{
				// cập nhật tọa độ
				updateTargetPosition(targetBody, Vector2(0, 0));
				return true;
			}
			else
			{
				if (_CollisionDirection.y == targetVelocity.y * -1) 
				{
					updateTargetPosition(targetBody, Vector2(0, 0));
				}
			}
		}
	}
	else
	{
		float moveX, moveY;
		if (isColliding(targetBody, otherBody, moveX, moveY, DeltaTime))
		{
			// cập nhật tọa độ
			switch (collisionAction)
			{
			case 0:
				updateTargetPosition(targetBody, Vector2(moveX, moveY));
				break;
			default:
				break;
			}

			return true;
		}
	}
	return false;
}

void Collision::updateTargetPosition(Body &Object, Vector2 move)
{
	if(move == Vector2(0, 0))
		Object.SetPosition(_CollisionPosition.x, _CollisionPosition.y);
	else {
		Object.SetPosition(Object.GetPosition().x + move.x, Object.GetPosition().y + move.y);
	}
}

void Collision::Push(Body &object)
{
	//float magnitude = (sqrt(object.GetTotalVelocity(DeltaTime).x * object.GetTotalVelocity(DeltaTime).x + object.GetTotalVelocity(DeltaTime).y * object.GetTotalVelocity(DeltaTime).y)) * _RemainingTime;
	//float dotprod = object.GetTotalVelocity(DeltaTime)().X * _CollisionDirection.X + object.GetTotalVelocity(DeltaTime)().Y * _CollisionDirection.Y;
	/*if (dotprod > 0.0f)
	dotprod = 1.0f;
	else if (dotprod < 0.0f)
	dotprod = -1.0f;*/
	//Vector2 NewObjectVelocity = Vector2(dotprod * _CollisionDirection.Y * magnitude, dotprod * _CollisionDirection.X * magnitude);
	//object.SetVelocity(NewObjectVelocity);
}

void Collision::Slide(Body &object)
{
	/*float dotprod = (object.GetTotalVelocity(DeltaTime)().X * _CollisionDirection.X + object.GetTotalVelocity(DeltaTime)().Y * _CollisionDirection.Y) * _RemainingTime;
	Vector2 NewObjectVelocity = Vector2(dotprod * _CollisionDirection.Y, dotprod * _CollisionDirection.X);*/
	/*object.SetVelocity(NewObjectVelocity);*/
}

void Collision::Deflect(Body &object)
{
	/*Vector2 RemainingVelocity = Vector2(object.GetTotalVelocity(DeltaTime)().X * _RemainingTime, object.GetTotalVelocity(DeltaTime)().Y * _RemainingTime);
	if (abs(_CollisionDirection.X) > 0.0001f)
	{
	RemainingVelocity.X = -RemainingVelocity.X;
	}
	if (abs((_CollisionDirection.Y) > 0.0001f))
	{
	RemainingVelocity.Y = -RemainingVelocity.Y;
	}
	object.SetVelocity(RemainingVelocity);*/
}