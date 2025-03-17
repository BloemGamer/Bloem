#pragma once

#include <filesystem>
#include <vector>
#include <functional>
#include <stack>

#ifndef __max
    #define __max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef __min
	#define __min(a,b) (((a) < (b)) ? (a) : (b))
#endif


#define AMOUNT_MEMORYCELLS 9

class Bloem
{
private:
	
	std::size_t extra_functions = 0;
	std::size_t amount_basic_instructions = 8;

	std::filesystem::path filename;
	std::vector<long long> jump_stack;
	std::stack<long long> function_stack;
	

	int counting_base = 10;
	void add_new_instructions(std::string str);
	void add_jump_stack(long long index, long long line_index_);
	void add_in_file_function(long long fn_index, long long line_index_);

public:
	void* memory_cells[AMOUNT_MEMORYCELLS];
	void* memory_cells_sw[AMOUNT_MEMORYCELLS];
	bool exit_ = false;
	
	std::size_t line_index = 0;
	std::vector<std::function<void(void)>> functions;
	std::vector<long long> line_index_fn;
	std::vector<std::vector<long long>> instructions;

	int from_jump_stack(long long index);
	void setup(std::filesystem::path filename_);
	void setup(void);
	void run();
	void add_function(std::size_t index, std::function<void(void)> func);
	void add_standard_functions(void);
	void go_to_(std::size_t place);
	void got_to_fn(long long line_index_);
	void return_fn(void);

	Bloem();
	Bloem(std::filesystem::path filename_);
	~Bloem();
};

extern Bloem* global_bloem;

