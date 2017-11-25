#include <unordered_map>
#include <queue>
#include <string>
//
#include <v16/architecture.hpp>
#include <v16/instruction.hpp>
#include <tokenizer.hpp>

class Parser
{
	public:
	void parse(std::queue<Token> &tokens);

	std::queue<Word> getWords();
	private:
	Opcode stringToOpcode(std::string string);
	Mode::Type stringToModeType(std::string string);

	static void stringToLower(std::string &string);
	static Word stringToWord(std::string const &string);
	std::unordered_map<std::string, Word> identifiers;
	std::queue<Word> words;
};
