#include <filesystem>
#include <fstream>
#include "bloem.hpp"

void bloem::setup(char* filename_)
{
	std::size_t amount_lines;
	// std::size_t commented_lines = 0;
	std::string text_file;
	std::string file;
	filename.replace_filename(filename_);
	std::ifstream input(filename);
	// uintmax_t length = std::filesystem::file_size(filename) / sizeof(char);
	for(amount_lines = 0; std::getline(input, text_file); amount_lines++)
	{
		// if(text_file.starts_with((char*)"//"))
		// {
		// 	continue;
		// }
		// size_t start_comment = text_file.find("//");

		file.append(text_file, 0, text_file.find("//"));

	}

	input.close();
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