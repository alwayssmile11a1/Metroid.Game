#pragma once

#include <string>
#include <iterator>

class TMXTileLayer
{
private:
	std::string _LayerName;
	unsigned int _Width;
	unsigned int _Height;
	unsigned int** _Data;

public:
	TMXTileLayer();
	~TMXTileLayer();
	TMXTileLayer(const TMXTileLayer &tmxTileLayer);
	TMXTileLayer& operator=(const TMXTileLayer &tmxTileLayer);


	void SetAttributes(std::string name, unsigned int width, unsigned int height);
	void SetData(char* matrixCSV);

	std::string GetName();
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int** GetData();


};