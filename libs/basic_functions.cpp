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

void exit_bloem(void)
{
	std::cout << "\nExited with error code: "<< *(int*)global_bloem->memory_cells[1];
	return;
}