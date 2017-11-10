//useful functions
#pragma once
#include "..\extensions\directX9\Include\d3dx9.h"
#include <string>
#include <iostream>
#include <fstream>

LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath);

/* File loading helper functions */
bool LoadFile(std::string filePath, std::string &fileContents);