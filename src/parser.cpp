#include <cctype>
#include <cstdlib>
#include <stdexcept>
//
#include "parser.hpp"

void Parser::parse(std::vector<Token> const &tokens)
{
	if(tokens.front().type == Token::Type::IDENTIFIER)
	{
		identifiers[tokens.front().value] = static_cast<Word>(std::strtoul(tokens[1].value.c_str(), NULL, 0));
		return;
	}
}

Opcode Parser::stringToOpcode(std::string string)
{
	for(auto &i : string)
	{
		i = static_cast<char>(std::tolower(i));
	}
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
