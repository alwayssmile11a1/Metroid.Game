#include "TMXTileSet.h"

TMXTileSet::TMXTileSet()
{
	_FirstGid = 1;
	_TileWidth = 0;
	_TileHeight = 0;
	_TileCount = 0;
	_Columns = 0;
	_ImageWidth = 0;
	_ImageHeight = 0;
	_Texture = NULL;
}

void TMXTileSet::SetAttributes(std::string name, unsigned int firstGid, unsigned int tileWidth, unsigned int tileHeight,
	 unsigned int tileCount, unsigned int columns, std::string sourcePath, unsigned int imageWidth, unsigned int imageHeight)
{
	_FirstGid = firstGid;
	_Name = name;
	_SourcePath = sourcePath;
	_ImageWidth = imageWidth;
	_ImageHeight = imageHeight;
	_TileWidth = tileWidth;
	_TileHeight = tileHeight;
	_TileCount = tileCount;
	_Columns = columns;

	_Texture = new Texture(_SourcePath);
}

TMXTileSet::~TMXTileSet()
{
	if (_Texture != NULL)
	{
		delete _Texture;
		_Texture = NULL;
	}
}

TMXTileSet::TMXTileSet(const TMXTileSet &tmxTileSet)
{
	_FirstGid = tmxTileSet._FirstGid;
	_Name = tmxTileSet._Name;
	_SourcePath = tmxTileSet._SourcePath;
	_ImageWidth = tmxTileSet._ImageWidth;
	_ImageHeight = tmxTileSet._ImageHeight;
	_TileWidth = tmxTileSet._TileWidth;
	_TileHeight = tmxTileSet._TileHeight;
	_TileCount = tmxTileSet._TileCount;
	_Columns = tmxTileSet._Columns;

	_Texture = new Texture();
	*_Texture = *tmxTileSet._Texture;
}
TMXTileSet& TMXTileSet::operator=(const TMXTileSet &tmxTileSet)
{
	_FirstGid = tmxTileSet._FirstGid;
	_Name = tmxTileSet._Name;
	_SourcePath = tmxTileSet._SourcePath;
	_ImageWidth = tmxTileSet._ImageWidth;
	_ImageHeight = tmxTileSet._ImageHeight;
	_TileWidth = tmxTileSet._TileWidth;
	_TileHeight = tmxTileSet._TileHeight;
	_TileCount = tmxTileSet._TileCount;
	_Columns = tmxTileSet._Columns;

	_Texture = new Texture();
	*_Texture = *tmxTileSet._Texture;

	return *this;

}

Texture* TMXTileSet::GetTexture()
{
	return _Texture;
}

std::string TMXTileSet::GetName()
{
	return _Name;
}


std::string TMXTileSet::GetSourcePath()
{
	return _SourcePath;
}


unsigned int TMXTileSet::GetFirstGid()
{
	return _FirstGid;
}

unsigned int TMXTileSet::GetImageWidth()
{
	return _ImageWidth;
}


unsigned int TMXTileSet::GetImageHeight()
{
	return _ImageHeight;
}


unsigned int TMXTileSet::GetTileWidth()
{
	return _TileWidth;
}


unsigned int TMXTileSet::GetTileHeight()
{
	return _TileHeight;
}


unsigned int TMXTileSet::GetTileCount()
{
	return _TileCount;
}

unsigned int TMXTileSet::GetColumns()
{
	return _Columns;
}