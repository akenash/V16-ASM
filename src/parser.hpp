#include <unordered_map>
#include <string>
//
#include <v16/architecture.hpp>
#include <v16/instruction.hpp>
#include <tokenizer.hpp>

class Parser
{
	public:
	void parse(std::vector<Token> const &tokens);
	private:
	Opcode stringToOpcode(std::string string);
	std::unordered_map<std::string, Word> identifiers;
	std::vector<Instruction> instructions;
};
