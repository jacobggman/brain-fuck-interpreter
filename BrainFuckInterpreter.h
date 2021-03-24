#pragma once
#include <stack>
#include <set>
#include <initializer_list>

#include "InputAbs.h"
#include "UnknownOpcode.h"

class CodeMem {
public:
	virtual void push(char a) = 0;
	virtual void init() = 0;
	virtual char get(int index) = 0;
};

class Mem {
public:
	virtual char get(int index) = 0;
	virtual void set(int index, char value) = 0;
	virtual void inc(int index) = 0;
	virtual void dec(int index) = 0;
	virtual int maxPointerValue() = 0;
};

class BrainFuckInterpreter
{
public:
	BrainFuckInterpreter(CodeMem* code, Mem* memory, InputAbs* input);
	~BrainFuckInterpreter();
	void readInput(const char* cArr, int size);
	// return true while not finished
	bool execute();

private:

	CodeMem* code;
	Mem* memory;
	InputAbs* input;
	int programCounter = 0;
	int pointerMem = 0;
	int programSize = 0;
	static const std::set<char> legalChars;
	std::stack<int> stack;
};
