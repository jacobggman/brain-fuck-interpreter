#pragma once

#include <stack>

class InputAbs
{
public:
	virtual char readChar() = 0;
	virtual void writeChar(char c) = 0;
};
