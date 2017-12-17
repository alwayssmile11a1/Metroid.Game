//this header contains every variable that should be use globally
#pragma once

#include "..\extensions\directX9\Include\d3d9.h"
#include "..\extensions\directX9\Include\d3dx9.h" //please read the readme.txt file if you have any problems with this include line. 
#include "..\input\Input.h"
#include "..\sound\MySound.h"
#include "..\console\Console.h"

//Direct3D variables
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddevice;
extern Sound sound;
//input 
extern Input input;

//initial screenwidth and screenheight
extern int screenWidth;
extern int screenHeight;
