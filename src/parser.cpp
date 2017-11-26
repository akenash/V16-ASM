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
	if(tokens.front().type == Token::Type::NUMBER)
	{
		words.push(stringToWord(tokens.front().value));
		return;
	}
	Opcode opcode = stringToOpcode(tokens.front().value);
	Instruction instr(opcode, {0x0000}, {0x0000});
	tokens.pop();
	if(tokens.empty())
	{
		words.push(instr.assemble());
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
	instr.A = A;
	if(tokens.empty())
	{
		words.push(instr.assemble());
		return;
	}
	Word X = 0x0000;
	if(tokens.front().type == Token::Type::IDENTIFIER)
	{
		X = identifiers.at(tokens.front().value);
		tokens.pop();
	}
	else if(tokens.front().type == Token::Type::NUMBER)
	{
		X = stringToWord(tokens.front().value);
		tokens.pop();
	}
	if(tokens.empty())
	{
		words.push(instr.assemble());
		words.push(X);
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
	instr.B = B;
	if(tokens.empty())
	{
		words.push(instr.assemble());
		words.push(X);
		return;
	}
	Word Y = 0x0000;
	if(tokens.front().type == Token::Type::IDENTIFIER)
	{
		Y = identifiers.at(tokens.front().value);
		tokens.pop();
	}
	else if(tokens.front().type == Token::Type::NUMBER)
	{
		Y = stringToWord(tokens.front().value);
		tokens.pop();
	}
	if(tokens.empty())
	{
		words.push(instr.assemble());
		words.push(X);
		words.push(Y);
		return;
	}
}

std::queue<Word> Parser::getWords()
{
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
	else if(string == "sdp") return SDP;
	else throw std::runtime_error("illegal instruction: " + string);
}

Mode::Type Parser::stringToModeType(std::string string)
{
	stringToLower(string);
	if(string == "m") return Mode::Type::M;
	else if(string == "r") return Mode::Type::R;
	else if(string == "i") return Mode::Type::I;
	else if(string == "h") return Mode::Type::H;
	else if(string == "p") return Mode::Type::P;
	else if(string == "s") return Mode::Type::S;
	else if(string == "a") return Mode::Type::A;
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
