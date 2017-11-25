#include <cctype>
#include <cstdlib>
#include <stdexcept>
//
#include "parser.hpp"

void Parser::parse(std::queue<Token> &tokens)
{
	if(tokens.empty()) return;
	if(tokens.front().type == Token::Type::IDENTIFIER)
	{
		std::string name = tokens.front().value;
		tokens.pop();
		identifiers[name] = stringToWord(tokens.front().value);
		return;
	}
	std::queue<Word> words;
	Opcode opcode = stringToOpcode(tokens.front().value);
	tokens.pop();
	if(tokens.empty())
	{
		lines.push({{opcode, {0x0000}, {0x0000}}, words});
		return;
	}
	bool indirect = false;
	Mode::Type type;
	if(tokens.front().value == "$")
	{
		indirect = true;
		tokens.pop();
	}
	type = stringToModeType(tokens.front().value);
	tokens.pop();
	Mode A(type, indirect);
	if(tokens.empty())
	{
		lines.push({{opcode, A, {0x0000}}, words});
		return;
	}
	if(tokens.front().type == Token::Type::IDENTIFIER)
	{
		words.push(identifiers.at(tokens.front().value));
		tokens.pop();
	}
	else if(tokens.front().type == Token::Type::NUMBER)
	{
		words.push(stringToWord(tokens.front().value));
		tokens.pop();
	}
	else
	{
		words.push(0x0000);
	}
	if(tokens.empty())
	{
		lines.push({{opcode, A, {0x0000}}, words});
		return;
	}
	indirect = false;
	if(tokens.front().value == "$")
	{
		indirect = true;
		tokens.pop();
	}
	type = stringToModeType(tokens.front().value);
	tokens.pop();
	Mode B(type, indirect);
	if(tokens.empty())
	{
		lines.push({{opcode, A, B}, words});
		return;
	}
	if(tokens.front().type == Token::Type::IDENTIFIER)
	{
		words.push(identifiers.at(tokens.front().value));
		tokens.pop();
	}
	else if(tokens.front().type == Token::Type::NUMBER)
	{
		words.push(stringToWord(tokens.front().value));
		tokens.pop();
	}
	else
	{
		words.push(0x0000);
	}
	if(tokens.empty())
	{
		lines.push({{opcode, A, B}, words});
		return;
	}
}

std::queue<Word> Parser::assemble()
{
	std::queue<Word> words;
	while(!lines.empty())
	{
		words.push(lines.front().instr.assemble());
		while(!lines.front().words.empty())
		{
			words.push(lines.front().words.front());
			lines.front().words.pop();
		}
		lines.pop();
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
	else if(string == "api") return API;
	else if(string == "apo") return APO;
	else throw std::runtime_error("illegal instruction: " + string);
}

Mode::Type Parser::stringToModeType(std::string string)
{
	stringToLower(string);
	if(string == "m") return Mode::Type::M;
	else if(string == "r") return Mode::Type::R;
	else if(string == "h") return Mode::Type::H;
	else if(string == "p") return Mode::Type::P;
	else if(string == "t") return Mode::Type::T;
	else if(string == "s") return Mode::Type::S;
	else if(string == "f") return Mode::Type::F;
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
