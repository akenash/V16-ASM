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

	std::vector<Word> assemble();
	private:
	Opcode stringToOpcode(std::string string);
	ModeType stringToModeType(std::string string);

	static void stringToLower(std::string &string);
	static Word stringToWord(std::string const &string);
	std::unordered_map<std::string, Word> identifiers;
	std::vector<Instruction> instructions;
	std::vector<std::vector<Word>> values;
};
