#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <functional>
#include <cstring>
#include "bloem.hpp"

void bloem::setup(char* filename_)
{
	std::size_t amount_lines;
	std::string text_file;
	std::string file;
	filename.replace_filename(filename_);
	std::ifstream input(filename);
	for(amount_lines = 0; std::getline(input, text_file); amount_lines++)
	{
		if((std::size_t)text_file.find("#extra_functions") != std::string::npos)
		{
			extra_functions = __max(extra_functions, atoll(text_file.c_str() + std::strlen((char*)"#extra_functions ")));
			continue;
		}
		file.append(text_file, 0, text_file.find("//"));
		file.append("\n");

	}

	
	input.close();
	functions.resize(__max(functions.size(), extra_functions + amount_basic_instructions));
	std::cout << file;

}

void bloem::run()
{

}


bloem::bloem(/* args */)
{
}

bloem::~bloem()
{
}