#ifndef LABEL_H
#define LABEL_H

#include "Font.h"
#include "..\camera\Camera.h"
#include "..\math\Vector2.h"

class Label
{
private:
	Vector2 _Position;
	Vector2 _Size;
	float x, y, width, height;
	LPCWSTR _Text;

	Font *_Font;

public:
	Label();
	~Label();

	void SetText(std::string &text);
	Label(const std::string &text, Font *font, float x, float y, float width, float height);

	void Draw(Camera *cam);

};

#endif
