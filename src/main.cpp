#include <iostream>
#include <tokenizer.hpp>

int main()
{
	auto tokens = tokenize("CPY $P:0x2000  R%PTRREG");
	for(auto const &i : tokens )
	{
		std::cout << i.value << ", ";
	}
	std::cout << "\n";
	for(auto const &i : tokens )
	{
		switch(i.type)
		{
			case Token::Type::IRRELEVANT: std::cout << "I"; break;
			case Token::Type::NUMBER: std::cout << "N"; break;
			case Token::Type::MODE: std::cout << "M"; break;
			case Token::Type::IDENTIFIER: std::cout << "C"; break;
			case Token::Type::OPCODE: std::cout << "O"; break;
		}
	}
}
