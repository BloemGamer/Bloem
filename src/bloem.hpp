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
	std::size_t amount_basic_instructions = 5;
	std::size_t line_index = 0;

	std::filesystem::path filename;
	std::vector<long long> jump_stack;
	

	int counting_base = 10;
	void add_new_instructions(std::string str);
	void add_jump_stack(long long index, long long line_index_);
	
public:
	void* memory_cells[AMOUNT_MEMORYCELLS];
	void* memory_cells_sw[AMOUNT_MEMORYCELLS];
	bool exit_ = false;
	
	std::vector<std::function<void(void)>> functions;

	int from_jump_stack(long long index);
	void setup(std::filesystem::path filename_);
	void setup(void);
	void run();
	void add_function(std::size_t index, std::function<void(void)> func);
	void add_standard_functions(void);
	void go_to_(std::size_t place);

	Bloem();
	Bloem(std::filesystem::path filename_);
	~Bloem();
};

extern Bloem* global_bloem;

