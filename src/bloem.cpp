#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <cstring>
#include <algorithm>
#include <regex>
#include "bloem.hpp"
#include "../libs/basic_functions.hpp"

Bloem* global_bloem;

static std::vector<std::string> split(std::string s, std::string delimiter);

void Bloem::add_new_instructions(std::string str)
{
	bool end = true;
	if(!str.size())
		return;
	std::vector<std::string> lines = split(str, ";");
	for(size_t i = 0; i < lines.size(); i++)
	{
		if(!lines[i].size())
		{
			continue;
		}
		
		std::vector<std::string> line = split(lines[i], " ");
		for(size_t j = 0; j < line.size(); j++)
		{
			if(line[j].size())
			{
				instructions.resize(instructions.size() + 1);
				end = false;
				break;
			}
		}
		if(end)
		{
			return;
		}
		
		for(size_t j = 0; j < line.size(); j++)
		{
			if(!line[j].size())
			{
				continue;
			}
			instructions[instructions.size() - 1].push_back(strtoll(line[j].c_str(), 0, counting_base));
		}
	}
}

void Bloem::setup(std::filesystem::path filename_)
{
	filename.replace_filename(filename_);
	setup();
}

void Bloem::setup(void)
{
	global_bloem = this;
	std::size_t amount_lines;
	std::string text_file;
	std::string file;
	
	std::ifstream input(filename);
	instructions.clear();


	for(amount_lines = 0; std::getline(input, text_file); amount_lines++)
	{
		std::size_t place;
		if((place = text_file.find("#extra_functions")) != std::string::npos)
		{
			extra_functions = __max(extra_functions, std::atoll(text_file.c_str() + std::strlen((char*)"#extra_functions ") + place));
			continue;
		}
		if((place = text_file.find("#HEX")) != std::string::npos)
		{
			add_new_instructions(file);
			counting_base = 16;
			file.clear();
			continue;
		}
		if((place = text_file.find("#DEC")) != std::string::npos)
		{
			add_new_instructions(file);
			counting_base = 10;
			file.clear();
			continue;
		}
		
		file.append(text_file, 0, text_file.find("//"));
		file.append(" ");
	}

	

	add_new_instructions(file);
	file.clear();
	input.close();
	functions.resize(__max(functions.size(), extra_functions + amount_basic_instructions));
	add_standard_functions();
}

void Bloem::run()
{
	global_bloem = this;
	std::size_t place;
	for(place = 0; place < instructions.size(); place++)
	{
		if(exit_ == true)
		{
			return;
		}
		if(instructions[place].size() == 0)
			continue;
		for(size_t place_memorycell = 1; place_memorycell < __min(AMOUNT_MEMORYCELLS, instructions[place].size()); place_memorycell++)
		{
			memory_cells[place_memorycell] = (void*)&instructions[place][place_memorycell];
		}
		functions[instructions[place][0]]();
	}
}

void Bloem::add_function(std::size_t index, std::function<void(void)> func)
{
	if(index >= functions.size()) 
		std::cerr << "Couldn't add function, not enough memory reserved, add more memory with \"#extra_functions\" or changing the \"extra_functions\" variable";
	functions[index] = func;
}

void test(void);

void Bloem::add_standard_functions(void)
{
	amount_basic_instructions = 1;
	functions.resize(__max(functions.size(), extra_functions + amount_basic_instructions));
	add_function(0, exit_bloem);
}

void test(void)
{

}

Bloem::Bloem()
{
	
}

Bloem::Bloem(std::filesystem::path filename_)
{
	filename.replace_filename(filename_);
}

Bloem::~Bloem()
{

}








static std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
	{
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back(s.substr (pos_start));
    return res;
}