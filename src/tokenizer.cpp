#include <cstdint>
#include "tokenizer.hpp"

CharType getCharType(char character)
{
	switch(ASCIITypes[static_cast<uint8_t>(character)])
	{
		case 'L':
			return CharType::LETTER;
		case 'S':
			return CharType::SIGN;
		case 'D':
			return CharType::DIGIT;
		default:
		case 'I':
			return CharType::IRRELEVANT;
	}
}

std::vector<Token> tokenize(std::string const &line)
{
	std::vector<Token> tokens;
	Token buffer = {Token::Type::IRRELEVANT, ""};

	for(auto ch : line)
	{
		CharType type = getCharType(ch);
		switch(type)
		{
		case CharType::DIGIT:
			if(buffer.type != Token::Type::NUMBER)
			{
				buffer.type = Token::Type::NUMBER;
				buffer.value = ch;
			}
			else
			{
				buffer.value += ch;
			}
			break;

		case CharType::LETTER:
			if(buffer.type == Token::Type::IRRELEVANT || buffer.type == Token::Type::NUMBER ||
				buffer.type == Token::Type::IDENTIFIER)
			{
				buffer.value += ch;
			}
			else if(buffer.type == Token::Type::MODE)
			{
				buffer.type = Token::Type::IDENTIFIER;
				buffer.value = ch;
			}
			break;

		case CharType::SIGN:
			if(tokens.empty())
			{
				buffer.type = Token::Type::IDENTIFIER;
			}
			else if(buffer.value == "")
			{
				buffer.value = ch;
				buffer.type = Token::Type::MODE;
			}
			else
			{
				buffer.type = Token::Type::MODE;
			}
			tokens.push_back(buffer);
			buffer.type = Token::Type::MODE;
			buffer.value = "";
			break;

		case CharType::IRRELEVANT:
			if(tokens.empty())
			{
				buffer.type = Token::Type::OPCODE;
				tokens.push_back(buffer);
			}
			else if(buffer.type != Token::Type::IRRELEVANT && buffer.value != "")
			{
				tokens.push_back(buffer);
			}
			buffer.type = Token::Type::IRRELEVANT;
			buffer.value = "";
			break;
		}
	}
	if(buffer.type != Token::Type::IRRELEVANT)
	{
		tokens.push_back(buffer);
	}
	return tokens;
}
