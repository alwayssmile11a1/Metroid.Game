#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::isCollide(Sprite* targetObjectSprite, Sprite* otherObjectSprite, float dt, DWORD DeltaTime)
{
	//SweptAABB
	// vận tốc mỗi frame
	Vector2 otherObjectVelocity = Vector2(otherObjectSprite->GetVelocity().X * dt / 1000, otherObjectSprite->GetVelocity().Y * dt / 1000);
	Vector2 targetObjectVelocity = Vector2(targetObjectSprite->GetVelocity().X * dt / 1000, targetObjectSprite->GetVelocity().Y * dt / 1000);
	Vector2 tempVelocity = targetObjectVelocity;

	if (otherObjectVelocity != Vector2(0, 0))
	{
		tempVelocity = otherObjectVelocity - targetObjectVelocity;
	}

	// tính toán dx entry và dx exit
	// dx
	if (tempVelocity.X > 0.0f)
	{
		_dxEntry = (otherObjectSprite->GetPosition().X - otherObjectSprite->GetSize().X / 2) - (targetObjectSprite->GetPosition().X + targetObjectSprite->GetSize().X /2);
		_dxExit = (otherObjectSprite->GetPosition().X + otherObjectSprite->GetSize().X / 2) - (targetObjectSprite->GetPosition().X - targetObjectSprite->GetSize().X / 2);
	}
	else
	{
		_dxEntry = (otherObjectSprite->GetPosition().X + otherObjectSprite->GetSize().X / 2) - (targetObjectSprite->GetPosition().X - targetObjectSprite->GetSize().X / 2);
		_dxExit = (otherObjectSprite->GetPosition().X - otherObjectSprite->GetSize().X / 2) - (targetObjectSprite->GetPosition().X + targetObjectSprite->GetSize().X / 2);
	}

	// dy
	if (tempVelocity.Y > 0.0f)
	{
		_dyEntry = (otherObjectSprite->GetPosition().Y + otherObjectSprite->GetSize().Y / 2) - (targetObjectSprite->GetPosition().Y - targetObjectSprite->GetSize().Y / 2);
		_dyExit = (otherObjectSprite->GetPosition().Y - otherObjectSprite->GetSize().Y / 2) - (targetObjectSprite->GetPosition().Y + targetObjectSprite->GetSize().Y / 2);
	}
	else
	{
		_dyEntry = (otherObjectSprite->GetPosition().Y - otherObjectSprite->GetSize().Y / 2) - (targetObjectSprite->GetPosition().Y + targetObjectSprite->GetSize().Y / 2);
		_dyExit = (otherObjectSprite->GetPosition().Y + otherObjectSprite->GetSize().Y / 2) - (targetObjectSprite->GetPosition().Y - targetObjectSprite->GetSize().Y / 2);
	}

	// tìm thời gian va chạm 
	if (tempVelocity.X == 0)
	{
		// chia cho 0 ra vô cực
		_txEntry = -std::numeric_limits<float>::infinity();
		_txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		_txEntry = _dxEntry / tempVelocity.X;
		_txExit = _dxExit / tempVelocity.X;
	}

	if (tempVelocity.Y == 0)
	{
		_tyEntry = -std::numeric_limits<float>::infinity();
		_tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		_tyEntry = _dyEntry / tempVelocity.Y;
		_tyExit = _dyExit / tempVelocity.Y;
	}

	// thời gian va chạm
	// va chạm khi x và y CÙNG chạm => thời gian va chạm trễ nhất giữa x và y
	float entryTime = max(_txEntry, _tyEntry);
	// hết va chạm là 1 trong 2 x, y hết va chạm => thời gian sớm nhất để kết thúc va chạm
	float exitTime = min(_txExit, _tyExit);

	// .
	// object không va chạm khi:
	// nếu thời gian bắt đầu va chạm hơn thời gian kết thúc va chạm
	// thời gian va chạm x, y nhỏ hơn 0 (chạy qua luôn, 2 thằng đang đi xa ra nhau)
	// thời gian va chạm x, y lớn hơn 1 (còn xa quá chưa thể va chạm)
	if (entryTime > exitTime || _txEntry < 0.0f && _tyEntry < 0.0f || _txEntry > 1.0f || _tyEntry > 1.0f)
	{
		// không va chạm trả về 1 đi tiếp bt
		_CollisionTime = 1.0f;
		return;
	}

	// nếu việc xảy ra va chạm nằm trên trục x 
	if (_txEntry > _tyEntry)
	{
		// xét x
		// nếu vật a nằm bên phải vật b => vật a va chạm cạnh bên phải của hình bao vật b
		if (_dxEntry < 0.0f)
		{
			_CollisionDirection.X = 1.0f;
			_CollisionDirection.Y = 0.0f;
		}
		else //nếu vật a nằm bên trái vật b => vật a va chạm cạnh bên trái của hình bao vật b
		{
			_CollisionDirection.X = -1.0f;
			_CollisionDirection.Y = 0.0f;
		}
	}
	else //nếu việc xảy ra va chạm nằm trên trục y
	{
		// xét y
		//nếu vật a nằm bên dưới vật b => vật a sẽ va chạm cạnh dưới hình bao vât b
		if (_dyEntry < 0.0f) 
		{
			_CollisionDirection.X = 0.0f;
			_CollisionDirection.Y = 1.0f;
		}
		else //nếu vật a nằm bên trên vật b => vật a sẽ va chạm cạnh trên hình bao vât b
		{
			_CollisionDirection.X = 0.0f;
			_CollisionDirection.Y = -1.0f;
		}
	}

	_CollisionTime = entryTime;
	_RemainingTime = DeltaTime - entryTime;
}

RECT Collision::getSweptBroadphaseRect(Sprite* object, float dt)
{
	// vận tốc mỗi frame
	Vector2 velocity = Vector2(object->GetVelocity().X * dt / 1000, object->GetVelocity().Y * dt / 1000);
	
	RECT rect;
	rect.top = velocity.Y > 0 ? (object->GetPosition().Y - object->GetSize().Y / 2) + velocity.Y : object->GetPosition().Y - object->GetSize().Y / 2;
	rect.bottom = velocity.Y > 0 ? object->GetPosition().Y + object->GetSize().Y / 2 : object->GetPosition().Y + object->GetSize().Y / 2 + velocity.Y;
	rect.left = velocity.X > 0 ? object->GetPosition().X - object->GetSize().X / 2 : object->GetPosition().X - object->GetSize().X / 2 + velocity.X;
	rect.right = velocity.X > 0 ? object->GetPosition().X + object->GetSize().X / 2 + velocity.X : object->GetPosition().X + object->GetSize().X / 2;

	return rect;
}

bool Collision::isColliding(Sprite* targetObjectSprite, Sprite* otherObjectSprite, float& moveX, float& moveY, float dt)
{
	moveX = moveY = 0.0f;
	//auto myRect = _target->getBounding();
	//auto otherRect = otherObject->getBounding();

	float left = otherObjectSprite->GetPosition().X - otherObjectSprite->GetSize().X / 2 - (targetObjectSprite->GetPosition().X + targetObjectSprite->GetSize().X / 2);
	float top = otherObjectSprite->GetPosition().Y - otherObjectSprite->GetSize().Y / 2 - (targetObjectSprite->GetPosition().Y + targetObjectSprite->GetSize().Y / 2);
	float right = otherObjectSprite->GetPosition().X + otherObjectSprite->GetSize().X / 2 - (targetObjectSprite->GetPosition().X - targetObjectSprite->GetSize().X / 2);
	float bottom = otherObjectSprite->GetPosition().Y + otherObjectSprite->GetSize().Y / 2 - targetObjectSprite->GetPosition().Y - targetObjectSprite->GetSize().Y / 2;

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

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}