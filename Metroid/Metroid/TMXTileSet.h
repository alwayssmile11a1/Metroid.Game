#pragma once

#include <string>
#include "Texture.h"

class TMXTileSet
{
private:
	std::string _Name;
	unsigned int _FirstGid;
	unsigned int _TileWidth;
	unsigned int _TileHeight;
	unsigned int _TileCount;
	unsigned int _Columns;
	std::string _SourcePath;
	unsigned int _ImageWidth;
	unsigned int _ImageHeight;
	Texture *_Texture;

public:
	TMXTileSet();
	~TMXTileSet();
	TMXTileSet(const TMXTileSet &tmxTileSet);
	TMXTileSet& operator=(const TMXTileSet &tmxTileSet);

	void SetAttributes(std::string name, unsigned int firstGid, unsigned int tileWidth, unsigned int tileHeight , 
		unsigned int tileCount, unsigned int columns, std::string sourcePath, unsigned int imageWidth, unsigned int imageHeight);

	std::string GetName();
	std::string GetSourcePath();
	unsigned int GetColumns();
	unsigned int GetFirstGid();
	unsigned int GetImageWidth();
	unsigned int GetImageHeight();
	unsigned int GetTileWidth();
	unsigned int GetTileHeight();
	unsigned int GetTileCount();
	
	Texture	*GetTexture();

};