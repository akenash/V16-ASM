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

std::queue<Token> tokenize(std::string const &line)
{
	auto resetToken = [](Token &token) {token = {Token::Type::IRRELEVANT, ""};};

	std::queue<Token> tokens;
	Token buffer;
	resetToken(buffer);

	for(auto ch : line)
	{
		CharType type = getCharType(ch);
		switch(type)
		{
		case CharType::DIGIT:
			if(buffer.type != Token::Type::NUMBER)
			{
				buffer.type = Token::Type::NUMBER;
				buffer.value = "";
			}
			buffer.value += ch;
			break;

		case CharType::LETTER:
			if(buffer.value == "%")
			{
				buffer.type = Token::Type::IDENTIFIER;
				buffer.value = "";
			}
			buffer.value += ch;
			break;

		case CharType::SIGN:
			if(ch == '#')
			{
				return tokens;
			}
			else if(ch == '$')
			{
				buffer.type = Token::Type::MODE;
				buffer.value = "$";
				tokens.push(buffer);
			}
			else if(tokens.empty())
			{
				buffer.type = Token::Type::IDENTIFIER;
				tokens.push(buffer);
			}
			else if(buffer.value != "")
			{
				buffer.type = Token::Type::MODE;
				tokens.push(buffer);
			}
			resetToken(buffer);
			if(ch == '%') buffer.value = ch;
			break;

		case CharType::IRRELEVANT:
			if(tokens.empty() && buffer.value != "")
			{
				buffer.type = Token::Type::OPCODE;
			}
			if(buffer.value != "" && buffer.type != Token::Type::IRRELEVANT)
			{
				tokens.push(buffer);
			}
			resetToken(buffer);
			break;
		}
	}
	if(buffer.value != "" && buffer.type != Token::Type::IRRELEVANT)
	{
		tokens.push(buffer);
	}
	return tokens;
}
