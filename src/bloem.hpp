#pragma once

#include <filesystem>
#include <vector>
#include <functional>

#define AMOUNT_MEMORYCELLS 9

class Bloem
{
private:
	std::vector<std::vector<long long>> instructions;
	
	std::size_t extra_functions = 0;
	std::size_t amount_basic_instructions = 1;
	std::filesystem::path filename;

	int counting_base = 10;
	void add_new_instructions(std::string str);
public:
	void* memory_cells[AMOUNT_MEMORYCELLS];
	
	std::vector<std::function<void(void)>> functions;
	bool exit_ = false;

	void setup(std::filesystem::path filename_);
	void setup(void);
	void run();
	void add_function(std::size_t index, std::function<void(void)> func);
	void add_standard_functions(void);

	Bloem();
	Bloem(std::filesystem::path filename_);
	~Bloem();
};

extern Bloem* global_bloem;

