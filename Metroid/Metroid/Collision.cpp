#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::isCollide(Sprite &targetObjectSprite, Sprite &otherObjectSprite, DWORD DeltaTime)
{
	//tính toán dx entry và dx exit, có 2 trường hợp là vật a di chuyển ngược và xuôi với trục toạ độ
	tempvx = targetObjectSprite.GetVelocity().X - otherObjectSprite.GetVelocity().X;
	tempvy = targetObjectSprite.GetVelocity().Y - otherObjectSprite.GetVelocity().Y;
	if (tempvx > 0.0f)
	{
		dxentry = (otherObjectSprite.GetPosition().X - otherObjectSprite.GetSize().X / 2) - (targetObjectSprite.GetPosition().X + targetObjectSprite.GetSize().X / 2);
		dxexit = (otherObjectSprite.GetPosition().X + otherObjectSprite.GetSize().X / 2) - (targetObjectSprite.GetPosition().X - targetObjectSprite.GetSize().X / 2);
	}
	else
	{
		dxentry = (otherObjectSprite.GetPosition().X + otherObjectSprite.GetSize().X / 2) - (targetObjectSprite.GetPosition().X - targetObjectSprite.GetSize().X / 2);
		dxexit = (otherObjectSprite.GetPosition().X - otherObjectSprite.GetSize().X / 2) - (targetObjectSprite.GetPosition().X + targetObjectSprite.GetSize().X / 2);
	}

	//tính toán dy entry và exit, tương tự với dx entry/ exit
	if (tempvy > 0.0f)
	{
		dyentry = (otherObjectSprite.GetPosition().Y - otherObjectSprite.GetSize().Y / 2) - (targetObjectSprite.GetPosition().Y + targetObjectSprite.GetSize().Y / 2);
		dyexit = (otherObjectSprite.GetPosition().Y + otherObjectSprite.GetSize().Y / 2) - (targetObjectSprite.GetPosition().Y - targetObjectSprite.GetSize().Y / 2);
	}
	else
	{
		dyentry = (otherObjectSprite.GetPosition().Y + otherObjectSprite.GetSize().Y / 2) - (targetObjectSprite.GetPosition().Y - targetObjectSprite.GetSize().Y / 2);
		dyexit = (otherObjectSprite.GetPosition().Y - otherObjectSprite.GetSize().Y / 2) - (targetObjectSprite.GetPosition().Y + targetObjectSprite.GetSize().Y / 2);
	}

	////tính toán tỉ lệ giữa delta d và d entry/exit
	//deltadx = tempvx * DeltaTime;
	//deltady = tempvy * DeltaTime;
	//if (deltadx == 0.0f) //tránh trường hợp a.velocity = 0 dẫn tới việc chia cho 0, nên ta gán x entry/ exit = +/-vô cùng
	//{
	//	xentry = -std::numeric_limits<float>::infinity();
	//	xexit = std::numeric_limits<float>::infinity();
	//}
	//else
	//{
	//	xentry = dxentry / deltadx;
	//	xexit = dxexit / deltadx;
	//}

	////tính toán t y entry/ exit, tương tự x entry/ exit
	//if (deltady == 0.0f)
	//{
	//	yentry = -std::numeric_limits<float>::infinity();
	//	yexit = std::numeric_limits<float>::infinity();
	//}
	//else
	//{
	//	yentry = dyentry / deltady;
	//	yexit = dyexit / deltady;
	//}

	//tính toán t x entry/ exit
	if (targetObjectSprite.GetVelocity().X == 0.0f) //tránh trường hợp a.velocity = 0 dẫn tới việc chia cho 0, nên ta gán x entry/ exit = +/-vô cùng
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
	if (targetObjectSprite.GetVelocity().Y == 0.0f)
	{
		tyentry = -std::numeric_limits<float>::infinity();
		tyexit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyentry = dyentry / (targetObjectSprite.GetVelocity().Y * DeltaTime);
		tyexit = dyexit / (targetObjectSprite.GetVelocity().Y * DeltaTime);
	}

	// tính toán thời gian va chạm và thoát khỏi thực sự của vật a chuyển động đối với vật b đứng yên
	tentry = max(txentry, tyentry);
	texit = min(txexit, tyexit);

	//sau khi tính toán được thời gian thực sự va chạm và thoát khỏi, ta kiểm tra xem việc va chạm có xảy ra hay không
	if ((tentry > texit) || //trường hợp không xảy ra va chạm 1: thời gian thực sự xảy ra va chạm > thời gian thực sự a thoát khỏi b

		(txentry < 0.0f && tyentry < 0.0f) || //trường hợp không xảy ra va chạm thứ 2: vật a có vận tốc = 0 dẫn đến x entry/ y entry = -vô cùng, hoặc vật a di chuyển hướng ra khỏi vật b

		(txentry > 1.0f) || (tyentry > 1.0f)) //trường hợp không xảy ra va chạm thứ 3: trong khoảng thời gian delta_time đang xét (thời gian của 1 frame) thì vật a di chuyển chưa tới vật b
	{
		_CollisionDirection.X = 0.0f;
		_CollisionDirection.Y = 0.0f;
		_CollisionTime = 1.0f;
		_RemainingTime = std::numeric_limits<float>::infinity();
		_CollisionPosition.X = 0.0f;
		_CollisionPosition.Y = 0.0f;
	}
	else //xảy ra va chạm, chia làm 4 trường hợp, tương ứng với 4 hướng va chạm của vật a so với vật b
	{
		if (txentry > tyentry)//nếu việc xảy ra va chạm nằm trên trục x 
		{
			if (dxentry < 0.0f)//nếu vật a nằm bên phải vật b => vật a va chạm cạnh bên phải của hình bao vật b
			{
				_CollisionDirection.X = -1.0f;
				_CollisionDirection.Y = 0.0f;
			}
			else //nếu vật a nằm bên trái vật b => vật a va chạm cạnh bên trái của hình bao vật b
			{
				_CollisionDirection.X = 1.0f;
				_CollisionDirection.Y = 0.0f;
			}
		}
		else//nếu việc xảy ra va chạm nằm trên trục y
		{
			if (dyentry < 0.0f)//nếu vật a nằm bên dưới vật b => vật a sẽ va chạm cạnh dưới hình bao vât b
			{
				_CollisionDirection.X = 0.0f;
				_CollisionDirection.Y = -1.0f;
			}
			else//nếu vật a nằm bên trên vật b => vật a sẽ va chạm cạnh trên hình bao vât b
			{
				_CollisionDirection.X = 0.0f;
				_CollisionDirection.Y = 1.0f;
			}
		}

		_CollisionTime = tentry;
		_RemainingTime = DeltaTime - tentry;
		/*_CollisionPosition.X = targetObjectSprite.GetPosition().X + tentry * tempvx;
		_CollisionPosition.Y = targetObjectSprite.GetPosition().Y + tentry * tempvy;*/
		_CollisionPosition.X = otherObjectSprite.GetPosition().X - otherObjectSprite.GetSize().X / 2 - targetObjectSprite.GetSize().X / 2;
		_CollisionPosition.Y = targetObjectSprite.GetPosition().Y + tentry * tempvy;
	}
}

RECT Collision::getSweptBroadphaseRect(Sprite &object, DWORD DeltaTime)
{
	// vận tốc mỗi frame
	Vector2 velocity = Vector2(object.GetVelocity().X * DeltaTime / 1000, object.GetVelocity().Y * DeltaTime / 1000);

	RECT rect;
	rect.top = velocity.Y > 0 ? (object.GetPosition().Y - object.GetSize().Y / 2) + velocity.Y : object.GetPosition().Y - object.GetSize().Y / 2;
	rect.bottom = velocity.Y > 0 ? object.GetPosition().Y + object.GetSize().Y / 2 : object.GetPosition().Y + object.GetSize().Y / 2 + velocity.Y;
	rect.left = velocity.X > 0 ? object.GetPosition().X - object.GetSize().X / 2 : object.GetPosition().X - object.GetSize().X / 2 + velocity.X;
	rect.right = velocity.X > 0 ? object.GetPosition().X + object.GetSize().X / 2 + velocity.X : object.GetPosition().X + object.GetSize().X / 2;

	return rect;
}

bool Collision::isColliding(Sprite &targetObjectSprite, Sprite &otherObjectSprite, float& moveX, float& moveY, float dt)
{
	moveX = moveY = 0.0f;
	//auto myRect = _target->getBounding();
	//auto otherRect = otherObject->getBounding();

	float left = otherObjectSprite.GetPosition().X - otherObjectSprite.GetSize().X / 2 - (targetObjectSprite.GetPosition().X + targetObjectSprite.GetSize().X / 2);
	float top = otherObjectSprite.GetPosition().Y - otherObjectSprite.GetSize().Y / 2 - (targetObjectSprite.GetPosition().Y + targetObjectSprite.GetSize().Y / 2);
	float right = otherObjectSprite.GetPosition().X + otherObjectSprite.GetSize().X / 2 - (targetObjectSprite.GetPosition().X - targetObjectSprite.GetSize().X / 2);
	float bottom = otherObjectSprite.GetPosition().Y + otherObjectSprite.GetSize().Y / 2 - targetObjectSprite.GetPosition().Y - targetObjectSprite.GetSize().Y / 2;

	// kt coi có va chạm không
	//  CÓ va chạm khi 
	//  left < 0 && right > 0 && top > 0 && bottom < 0
	//
	if (left > 0 || right < 0 || top < 0 || bottom > 0)
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

bool Collision::isColliding(RECT targetObjectRect, RECT otherObjectRect)
{
	float left = otherObjectRect.left - targetObjectRect.right;
	float top = otherObjectRect.top - targetObjectRect.bottom;
	float right = otherObjectRect.right - targetObjectRect.left;
	float bottom = otherObjectRect.bottom - targetObjectRect.top;

	//return (left > 0 || right < 0 || top < 0 || bottom > 0);
	if (left < 0) {
		return true;
	}
}

bool Collision::checkCollision(Sprite &targetObjectSprite, Sprite &otherObjectSprite, DWORD DeltaTime, int collisionAction)
{
	isCollide(targetObjectSprite, otherObjectSprite, DeltaTime);

	if (_CollisionTime < 1.0f)
	{
		if (_CollisionDirection == targetObjectSprite.GetDirection())
		{
			// cập nhật tọa độ
			updateTargetPosition(targetObjectSprite);
			return true;
		}
		else {
			return false;
		}
		//if (collisionAction == 0)
		//{
		//	//updateTargetPosition(targetObjectSprite);
		//	Deflect(targetObjectSprite);
		//}
	}
	//else
	//{
	//	float moveX, moveY;
	//	if (isColliding(targetObjectSprite, otherObjectSprite, moveX, moveY, DeltaTime))
	//	{
	//		auto side = this->getSide(otherObject);
	//		direction = side;

	//		if (otherObject->getPhysicsBodySide() == eDirection::NONE || (side & otherObject->getPhysicsBodySide()) != side)
	//			return true;

	//		// cập nhật tọa độ
	//		if (updatePosition)
	//			updateTargetPosition(otherObject, direction, false, GVector2(moveX, moveY));

	//		return true;
	//	}
	//}
	return false;
}

void Collision::updateTargetPosition(Sprite &Object)
{
	//Vector2 pos = Object.GetPosition();
	//if (txentry > tyentry)
	//{
	//	// xử lý cản left và right
	//	if (txentry < 1 && txentry > 0)
	//		pos.X += dxentry;
	//}
	//else
	//{
	//	// xử lý cản top và bot
	//	if (tyentry < 1 && tyentry > 0)
	//		pos.Y += dyentry;
	//}
	//Object.SetPosition(pos.X, pos.Y);
	Object.SetPosition(_CollisionPosition.X, _CollisionPosition.Y);
}

void Collision::Push(Sprite &object)
{
	float magnitude = (sqrt(object.GetVelocity().X * object.GetVelocity().X + object.GetVelocity().Y * object.GetVelocity().Y)) * _RemainingTime;
	//float dotprod = object.GetVelocity().X * _CollisionDirection.X + object.GetVelocity().Y * _CollisionDirection.Y;
	/*if (dotprod > 0.0f)
	dotprod = 1.0f;
	else if (dotprod < 0.0f)
	dotprod = -1.0f;*/
	//Vector2 NewObjectVelocity = Vector2(dotprod * _CollisionDirection.Y * magnitude, dotprod * _CollisionDirection.X * magnitude);
	//object.SetVelocity(NewObjectVelocity);
}

void Collision::Slide(Sprite &object)
{
	/*float dotprod = (object.GetVelocity().X * _CollisionDirection.X + object.GetVelocity().Y * _CollisionDirection.Y) * _RemainingTime;
	Vector2 NewObjectVelocity = Vector2(dotprod * _CollisionDirection.Y, dotprod * _CollisionDirection.X);*/
	/*object.SetVelocity(NewObjectVelocity);*/
}

void Collision::Deflect(Sprite &object)
{
	/*Vector2 RemainingVelocity = Vector2(object.GetVelocity().X * _RemainingTime, object.GetVelocity().Y * _RemainingTime);
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