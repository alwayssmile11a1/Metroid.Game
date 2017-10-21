#include "TexturePacker.h"

TexturePacker::TexturePacker()
{
	_Content.clear();
}

TexturePacker::~TexturePacker()
{

}

TexturePacker::TexturePacker(Texture* texture, std::string packerfilePath)
{
	//get file
	std::ifstream textureFile(packerfilePath);
	std::string line;

	//get the content of this file
	if (textureFile.is_open())
	{
		while (getline(textureFile, line))
		{
			_Content.append(line + " ");
		}
		textureFile.close();
	}

	_Texture = texture;;

}

std::vector<TextureRegion> TexturePacker::GetRegion(std::string regionName)
{

	std::vector<TextureRegion> regions;

	//get dimensions represented by a string
	std::string result = "";
	std::size_t first = _Content.find("<" + regionName + ">");
	std::size_t last = _Content.find("</" + regionName + ">");

	if (first != std::string::npos && last != std::string::npos)
	{
		result = _Content.substr(first + 3 + regionName.size(), last - first - 4 - regionName.size());
	}
	
	std::string::size_type sz;     // alias of size_t

	while (result != "")
	{
		//get rectLeft
		float rectLeft = std::stof(result, &sz);
		result = result.substr(sz);

		//get rectTop
		float rectTop = std::stof(result, &sz);
		result = result.substr(sz);

		//get rectWidth
		float rectWidth = std::stof(result, &sz);
		result = result.substr(sz);

		//get rectHeight
		float rectHeight = std::stof(result, &sz);
		result = result.substr(sz);
		
		TextureRegion textureRegion(_Texture, rectLeft, rectTop, rectWidth, rectHeight);
		regions.push_back(textureRegion);

	}

	return regions;


}

void TexturePacker::SetTexture(Texture *texture)
{
	_Texture = texture;
}

void TexturePacker::SetPacker(std::string packerfilePath)
{
	_Content.clear();
	//get file
	std::ifstream textureFile(packerfilePath);
	std::string line;

	//get the content of this file
	if (textureFile.is_open())
	{
		while (getline(textureFile, line))
		{
			_Content.append(line + " ");
		}
		textureFile.close();
	}
}