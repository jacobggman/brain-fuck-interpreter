#include <exception>
#include <string>

class UnknownOpcode : public std::exception {
	std::string errString;
public:

	UnknownOpcode(char opcode);

	const char* what() const throw () override;
};