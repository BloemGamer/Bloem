#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <cstring>
#include <algorithm>
#include <regex>
#include <stack>
#include "bloem.hpp"
#include "../libs/basic_functions.hpp"

Bloem* global_bloem;

static std::vector<std::string> split(std::string s, std::string delimiter);

void Bloem::add_in_file_function(long long fn_index, long long line_index_)
{
	if(fn_index >= 0)
	{
		std::cerr << "something went wrong with making the function";
		global_bloem->exit_ = true;
		return;
	}

	fn_index *= -1;
	line_index_fn.resize(__max(line_index_fn.size(), fn_index + 1));
	functions.resize(__max(functions.size(), fn_index + 1));

	line_index_fn[fn_index] = line_index_;
	add_function(fn_index, Bloem_fn::go_to_fn_);
}

void Bloem::got_to_fn(long long line_index_)
{
	function_stack.push(line_index);
	go_to_(line_index_);
}

void Bloem::return_fn(void)
{
	line_index = function_stack.top();
	function_stack.pop();
}

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
		if(instructions[instructions.size() - 1][0] == 2)
		{
			if(instructions[instructions.size() - 1].size() >= 2)
			{
				add_jump_stack(instructions[instructions.size() - 1][1], instructions.size() - 1);
			}
			else
			{
				exit_ = true;
				std::cerr << "Not enough arguments in the go_to place";
			}
		}
		if(instructions[instructions.size() - 1][0] < 0)
		{
			add_in_file_function(instructions[instructions.size() - 1][0], instructions.size() - 1);
		}
	}
}

void Bloem::add_jump_stack(long long index, long long line_index_)
{
	jump_stack.resize(__max(jump_stack.size(), index + 1));
	jump_stack[index] = line_index_;
	return;
}

int Bloem::from_jump_stack(long long index)
{
	if(index > (long long)jump_stack.size())
	{
		exit_ = true;
		std::cerr << "Can't find place to jump";
		return 0;
	}
	return jump_stack[index];
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
	for(line_index = 0; line_index < instructions.size(); line_index++)
	{
		if(exit_ == true)
		{
			return;
		}
		if(instructions[line_index].size() == 0)
		{
			continue;
		}
		if(instructions[line_index][0] == 2)
		{
			continue;
		}
		for(size_t place_memorycell = 1; place_memorycell < __min(AMOUNT_MEMORYCELLS, instructions[line_index].size()); place_memorycell++)
		{
			memory_cells[place_memorycell] = (void*)&instructions[line_index][place_memorycell];
		}
		if((long long)instructions[line_index][0] >= 0)
		{
			functions[instructions[line_index][0]]();
		}
	}
}

void Bloem::add_function(std::size_t index, std::function<void(void)> func)
{
	if(index >= functions.size()) 
		std::cerr << "Couldn't add function, not enough memory reserved, add more memory with \"#extra_functions\" or changing the \"extra_functions\" variable";
	functions[index] = func;
}

void Bloem::add_standard_functions(void)
{
	functions.resize(__max(functions.size(), extra_functions + amount_basic_instructions));
	add_function(0, Bloem_fn::exit_bloem);
	add_function(1, Bloem_fn::go_to);
	add_function(3, Bloem_fn::mov_to_mem);
	add_function(4, Bloem_fn::swap_mem);
	add_function(5, Bloem_fn::if_);
	add_function(6, Bloem_fn::return_);
}

void Bloem::go_to_(std::size_t place)
{
	line_index = place - 1;
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