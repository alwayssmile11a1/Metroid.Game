#ifndef CONSOLE_H
#define CONSOLE_H

#include <Windows.h>
#include <string>
#include "..\src\others\Utility.h"

class Console
{
public:
	Console();
	~Console();

	static void Log(const std::string &message);
};

#endif
