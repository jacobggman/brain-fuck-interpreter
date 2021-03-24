#include "BrainFuckInterpreter.h"

const std::set<char> BrainFuckInterpreter::legalChars = { '<', '>', ',', '.' ,'+', '-', '[', ']' };

BrainFuckInterpreter::BrainFuckInterpreter(CodeMem* code, Mem* memory, InputAbs* input)
{
	this->code = code;
	this->memory = memory;
	this->input = input;
}

BrainFuckInterpreter::~BrainFuckInterpreter()
{
	delete this->code;
	delete this->memory;
	delete this->input;
}

void BrainFuckInterpreter::readInput(const char* cArr, int size)
{
	code->init();
	for (size_t i = 0; i < size; i++)
	{
		char opcode = cArr[i];
		if (legalChars.find(opcode) != legalChars.end())
		{
			this->code->push(opcode);
			this->programSize++;
		}
	}
}

bool BrainFuckInterpreter::execute()
{
	char opcode = this->code->get(programCounter);
	switch (opcode)
	{
	case '>':
		pointerMem++;
		break;
	case '<':
		pointerMem--;
		if (pointerMem < 0)
		{
			pointerMem = memory->maxPointerValue();
		}
		break;
	case '+':
		this->memory->inc(pointerMem);
		break;
	case '-':
		this->memory->dec(pointerMem);
		break;
	case '[':
		this->stack.push(this->programCounter);
		break;
	case ']':
	{
		int pointer = this->stack.top();
		this->stack.pop();
		if (this->memory->get(this->pointerMem) != 0)
		{
			// it adding one after switch case
			this->programCounter = pointer - 1;
		}
		break;
	}
	case ',':
		this->memory->set(this->pointerMem, this->input->readChar());
		break;
	case '.':
		this->input->writeChar(this->memory->get(this->pointerMem));
		break;
	default:
		throw UnknownOpcode(opcode);
		break;
	}

	programCounter++;

	if (programCounter >= this->programSize)
	{
		return false;
	}
	return true;
}