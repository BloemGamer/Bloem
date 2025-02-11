#include <iostream>
#include <filesystem>
#include "src/bloem.hpp"

void func0(void);
void func1(void);

int main(int argc, char** argv)
{
	Bloem bloem;
	bloem.filename.replace_filename(*argv);
	bloem.filename.remove_filename();
	bloem.filename.append("test.txt");
	bloem.setup();
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