//this header contains every variable that should be use globally
#pragma once

#include "..\src\others\stdafx.h"
#include "Input.h"
//#include "MySound.h"

//Direct3D variables
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddevice;
//extern Sound sound;

//input 
extern Input input;

//initial screenwidth and screenheight
extern int screenWidth;
extern int screenHeight;
