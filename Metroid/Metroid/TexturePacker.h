#pragma once

#include "stdafx.h"
#include <string>
#include "TextureRegion.h"
#include "rapidxml.hpp"

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

