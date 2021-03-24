#include <vector>
#include <array>
#include <stdio.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <stdio.h>
#include <conio.h>

#include "BrainFuckInterpreter.h"

class Input : public InputAbs {
	// Inherited via InputAbs
	virtual char readChar() override
	{
		auto c = _getch();
		writeChar(c);
		return c;
	}
	virtual void writeChar(char c) override
	{
		putchar(c);
	}
};

class CodeMemImp : public CodeMem {
	std::vector<char> mem;

	virtual void push(char a) override
	{
		mem.push_back(a);
	}
	virtual void init() override
	{
		mem.reserve(3000);
	}

	virtual char get(int index) override
	{
		return mem[index];
	}
};

class MemImp : public Mem {
	std::array<char, 30000> mem = { 0 };

	virtual char get(int index) override
	{
		return mem[index];
	}
	virtual void set(int index, char value) override
	{
		mem[index] = value;
	}
	virtual void inc(int index) override
	{
		mem[index]++;
	}
	virtual void dec(int index) override
	{
		mem[index]--;
	}
	virtual int maxPointerValue() override
	{
		return 30000;
	}
};

int main() {
	BrainFuckInterpreter interpreter = BrainFuckInterpreter(new CodeMemImp(), new MemImp(), new Input());

	std::ifstream fileName("brainFuck.txt");
	std::string fileOpcodes((std::istreambuf_iterator<char>(fileName)),
		std::istreambuf_iterator<char>());

	interpreter.readInput(fileOpcodes.c_str(), fileOpcodes.size());
	while (interpreter.execute());
}