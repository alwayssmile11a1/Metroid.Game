#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace Shape
{

	class Rectangle
	{
	public:

		float x, y, width, height;

	public:
		Rectangle();
		~Rectangle();
		Rectangle(float x, float y, float width, float height);
		
		void Set(float x, float y, float width, float height);
		//void Set(float top, float left, float bottom, float right);

		//float GetTop();
		//float GetLeft();
		//float GetBottom();
		//float GetRight();

	};

}

#endif

