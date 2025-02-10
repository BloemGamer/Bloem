#pragma once

#include <filesystem>
#include <vector>
#include <functional>

#define AMOUNT_MEMORYCELLS 9

class bloem
{
private:
	std::vector<std::vector<long long>> instructions;
	
	std::size_t extra_functions = 0;
	std::size_t amount_basic_instructions = 0;
public:
	void* memory_cells[AMOUNT_MEMORYCELLS];
	std::filesystem::path filename;
	std::vector<std::function<void(void)>> functions;
	void setup(const char* filename = " ");
	void run();
	void add_function(std::function<void(void)> func, std::size_t index);
	void add_standard_functions(void);


	bloem(/* args */);
	~bloem();
};


