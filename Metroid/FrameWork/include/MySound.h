#pragma once
#include <iostream>
using namespace std;
#include "..\src\sound\DirectSound.h"

class Sound
{
private:
	CSoundManager *dsound;
public :
	bool DirectSound_Init(HWND hwnd);
	void DirectSound_Shutdown();
	CSound *LoadSound(string filename);
	void PlaySound(CSound *sound);
	void LoopSound(CSound *sound);
	void StopSound(CSound *sound);

};

