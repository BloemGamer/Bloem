#include <iostream>
#include <filesystem>
#include "src/bloem.hpp"

void func0(void);
void func1(void);

int main(int argc, char** argv)
{
	Bloem bloem;
	std::filesystem::path filename;
	filename.replace_filename(*argv);
	filename.remove_filename();
	filename.append("test.txt");
	bloem.setup(filename);
	bloem.add_function(1, func1);
	bloem.add_function(0, func0);
	bloem.run();
}

void func0(void)
{
	std::cout << "Hello world (func0)\n";
}

void func1(void)
{
	std::cout << "Hello world (func1)\n";
}