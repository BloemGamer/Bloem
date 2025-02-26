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

void Bloem_fn::go_to(void)
{
	switch(*(long long*)global_bloem->memory_cells[1])
	{
		case 0:
			global_bloem->go_to_(*(std::size_t*)global_bloem->memory_cells[2]);
			break;
		case 1:
			global_bloem->go_to_(global_bloem->from_jump_stack(*(std::size_t*)global_bloem->memory_cells[2]));
			break;
		default:
			std::cerr << "Not a valid input for \"jump to\"";
	}
	
}

void Bloem_fn::swap_mem(void)
{
	std::swap(global_bloem->memory_cells, global_bloem->memory_cells_sw);
}

void Bloem_fn::mov_to_mem(void)
{
	void** tmp;
	tmp = ((long long)global_bloem->memory_cells[1] ? global_bloem->memory_cells : global_bloem->memory_cells_sw);
	tmp[(long long)global_bloem->memory_cells[2]] = global_bloem->memory_cells[2];
}

void Bloem_fn::if_(void)
{
	switch((long long)global_bloem->memory_cells[1])
	{
		case 0:
			((long long)global_bloem->memory_cells[2] == (long long)global_bloem->memory_cells[1]) ? global_bloem->line_index++ : NULL;
		case 1:
			((long long)global_bloem->memory_cells[2] > (long long)global_bloem->memory_cells[1]) ? global_bloem->line_index++ : NULL;
		case 2:
			((long long)global_bloem->memory_cells[2] >= (long long)global_bloem->memory_cells[1]) ? global_bloem->line_index++ : NULL;
		case 3:
			((long long)global_bloem->memory_cells[2] < (long long)global_bloem->memory_cells[1]) ? global_bloem->line_index++ : NULL;
		case 4:
			((long long)global_bloem->memory_cells[2] <= (long long)global_bloem->memory_cells[1]) ? global_bloem->line_index++ : NULL;
		case 5:
			((long long)global_bloem->memory_cells[2] != (long long)global_bloem->memory_cells[1]) ? global_bloem->line_index++ : NULL;
	}
}