#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <functional>
#include <cstring>
#include <algorithm>
#include <regex>
#include "../src/bloem.hpp"
#include "basic_functions.hpp"



void Bloem_fn::exit_bloem(void)
{
	std::cout << "\nExited with error code: "<< *(int*)global_bloem->memory_cells[1];
	global_bloem->exit_ = true;
	return;
}

void Bloem_fn::jump_to(void)
{
	switch(*(long long*)global_bloem->memory_cells[1])
	{
		case 0:
			global_bloem->jump_to_(*(std::size_t*)global_bloem->memory_cells[2]);
			break;
		case 1:
			global_bloem->jump_to_(global_bloem->from_jump_stack(*(std::size_t*)global_bloem->memory_cells[2]));
			break;
		default:
			std::cerr << "Not a valid input for \"jump to\"";
	}
	
}
