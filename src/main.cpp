#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>
//
#include <tokenizer.hpp>
#include <parser.hpp>

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		std::cout << "usage: " << argv[0] << " INPUT OUTPUT\n";
		return 1;
	}
	std::string inputPath = argv[1];
	std::string outputPath = argv[2];
	std::ifstream input(inputPath);
	if(!input.good())
	{
		std::cout << "couldn't open input file: " << inputPath << "\n";
		return 1;
	}
	std::string line;
	Parser parser;
	while(std::getline(input, line))
	{
		auto tokens = tokenize(line);
		parser.parse(tokens);
	}
	input.close();
	auto words = parser.assemble();
	std::ofstream output(outputPath, std::ios::binary);
	if(!output.good())
	{
		std::cout << "couldn't open output file: " << outputPath << "\n";
		return 1;
	}
	std::size_t byteSize = words.size() * 2;
	uint8_t *bytes = new uint8_t[byteSize];
	for(unsigned i = 0; !words.empty(); i++, words.pop())
	{
		bytes[(i * 2) + 0] = static_cast<uint8_t>(words.front() >> 8);
		bytes[(i * 2) + 1] = static_cast<uint8_t>(words.front());
	}
	output.write(reinterpret_cast<char const *>(bytes), static_cast<std::streamsize>(byteSize));
	output.close();
}
