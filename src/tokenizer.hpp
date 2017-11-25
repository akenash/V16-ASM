#pragma once

#include <string>
#include <queue>

enum class CharType
{
	IRRELEVANT,
	LETTER,
	SIGN,
	DIGIT
};
// 129 because of trailing NULL terminator
const unsigned char ASCIITypes[129] =
	"IIIIIIIIIIIIIIII" //0  - 15
	"IIIIIIIIIIIIIIII" //16 - 31
	"IIISSSIIIIIIIIII" //32 - 47
	"DDDDDDDDDDSIIIII" //48 - 63
	"ILLLLLLLLLLLLLLL" //64 - 79
	"LLLLLLLLLLLIIIII" //80 - 95
	"ILLLLLLLLLLLLLLL" //96 -111
	"LLLLLLLLLLLIIIII";//112-127

struct Token
{
	enum Type
	{
		IRRELEVANT,
		NUMBER,
		MODE,
		IDENTIFIER,
		OPCODE,
	};

	Type type;
	std::string value;
};

CharType getCharType(char character);
std::queue<Token> tokenize(std::string const &line);
