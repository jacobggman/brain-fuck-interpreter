#include "UnknownOpcode.h"

UnknownOpcode::UnknownOpcode(char opcode)
{
	errString = "Unknown opcode: " + opcode;
}

const char* UnknownOpcode::what() const throw()
{
	return errString.c_str();
}