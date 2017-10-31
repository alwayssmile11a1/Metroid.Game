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


	void SetAttributes(const std::string& name, unsigned int width, unsigned int height);
	void SetData(char* matrixCSV);

	const std::string& GetName() const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	unsigned int** GetData() const;


};