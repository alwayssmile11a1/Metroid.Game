#ifndef TEXTUREPACKER_H
#define TEXTUREPACKER_H

#include "..\src\others\stdafx.h"
#include <string>
#include "TextureRegion.h"
#include "..\extensions\rapidxml\rapidxml.hpp"

//Get TextureRegion from a texture packer file
class TexturePacker: public GameObject
{
private:
	std::string _Content;
	Texture *_Texture;

public:
	TexturePacker();
	TexturePacker(Texture* texture, std::string packerfilePath);
	~TexturePacker();

	std::vector<TextureRegion> GetRegion(std::string regionName) const;
	void SetTexture(Texture *texture);
	void SetPacker(std::string packerfilePath);

};

#endif
