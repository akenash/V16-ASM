#include <cctype>
#include <cstdlib>
#include <stdexcept>
//
#include "parser.hpp"

void Parser::parse(std::vector<Token> const &tokens)
{
	unsigned i = 0;
	if(tokens.empty()) return;
	if(tokens.front().type == Token::Type::IDENTIFIER)
	{
		identifiers[tokens[0].value] = stringToWord(tokens[1].value);
		return;
	}
	Opcode opcode = stringToOpcode(tokens[i].value);
	i++;
	if(tokens.size() == 1)
	{
		instructions.push_back(Instruction(opcode, {0x0000}, {0x0000}));
		values.push_back({});
		return;
	}
	bool indirect = false;
	ModeType type;
	if(tokens[i].value == "$")
	{
		indirect = true;
		i++;
	}
	type = stringToModeType(tokens[i].value);
	i++;
	Mode A(type, indirect);
	if(i == tokens.size())
	{
		instructions.push_back(Instruction(opcode, A, {0x0000}));
		values.push_back({});
		return;
	}
	Word X;
	if(tokens[i].type == Token::Type::IDENTIFIER)
	{
		X = identifiers.at(tokens[i].value);
		i++;
	}
	else if(tokens[i].type == Token::Type::NUMBER)
	{
		X = stringToWord(tokens[i].value);
		i++;
	}
	else
	{
		X = 0x0000;
	}
	if(i == tokens.size())
	{
		instructions.push_back(Instruction(opcode, A, {0x0000}));
		values.push_back({X});
		return;
	}
	indirect = false;
	if(tokens[i].value == "$")
	{
		indirect = true;
		i++;
	}
	type = stringToModeType(tokens[i].value);
	i++;
	Mode B(type, indirect);
	if(i == tokens.size())
	{
		instructions.push_back(Instruction(opcode, A, B));
		values.push_back({X});
		return;
	}
	Word Y;
	if(tokens[i].type == Token::Type::IDENTIFIER)
	{
		Y = identifiers.at(tokens[i].value);
		i++;
	}
	else if(tokens[i].type == Token::Type::NUMBER)
	{
		Y = stringToWord(tokens[i].value);
		i++;
	}
	else
	{
		Y = 0x0000;
	}
	if(i == tokens.size())
	{
		instructions.push_back(Instruction(opcode, A, B));
		values.push_back({X, Y});
		return;
	}
}

std::vector<Word> Parser::assemble()
{
	std::vector<Word> words;
	for(unsigned i = 0; i < instructions.size(); i++)
	{
		words.push_back(instructions[i].assemble());
		for(unsigned j = 0; j < values[i].size(); j++)
		{
			words.push_back(values[i][j]);
		}
	}
	return words;
}

Opcode Parser::stringToOpcode(std::string string)
{
	stringToLower(string);
	if(string == "nop") return NOP;
	else if(string == "jmp") return JMP;
	else if(string == "cll") return CLL;
	else if(string == "ret") return RET;
	else if(string == "pnc") return PNC;
	else if(string == "mov") return MOV;
	else if(string == "cpy") return CPY;
	else if(string == "swp") return SWP;
	else if(string == "ieq") return IEQ;
	else if(string == "inq") return INQ;
	else if(string == "igt") return IGT;
	else if(string == "ilt") return ILT;
	else if(string == "igq") return IGQ;
	else if(string == "ilq") return ILQ;
	else if(string == "not") return NOT;
	else if(string == "or")  return OR ;
	else if(string == "and") return AND;
	else if(string == "xor") return XOR;
	else if(string == "rsf") return RSF;
	else if(string == "lsf") return LSF;
	else if(string == "add") return ADD;
	else if(string == "sub") return SUB;
	else if(string == "mul") return MUL;
	else if(string == "div") return DIV;
	else if(string == "mod") return MOD;
	else if(string == "snd") return SND;
	else throw std::runtime_error("illegal instruction: " + string);
}

ModeType Parser::stringToModeType(std::string string)
{
	stringToLower(string);
	if(string == "m") return ModeType::M;
	else if(string == "r") return ModeType::R;
	else if(string == "h") return ModeType::H;
	else if(string == "p") return ModeType::P;
	else if(string == "t") return ModeType::T;
	else if(string == "s") return ModeType::S;
	else if(string == "f") return ModeType::F;
	else throw std::runtime_error("illegal mode type: " + string);
}

void Parser::stringToLower(std::string &string)
{
	for(auto &i : string)
	{
		i = static_cast<char>(std::tolower(i));
	}
}

Word Parser::stringToWord(std::string const &string)
{
	return static_cast<Word>(std::strtoul(string.c_str(), NULL, 0));
}
