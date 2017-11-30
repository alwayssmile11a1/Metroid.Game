#ifndef CONSOLE_H
#define CONSOLE_H

#include "..\src\others\stdafx.h"

class Console
{
public:
	Console();
	~Console();

	static void Log(const std::string &message);
};

#endif
