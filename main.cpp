#include <iostream>
#include <filesystem>
#include "libs/bloem.hpp"

void func0(void);
void func1(void);

int main(int argc, char** argv)
{
	bloem bloem;
	bloem.filename.replace_filename(*argv);
	bloem.filename.remove_filename();
	bloem.filename.append("test.txt");
	bloem.setup();
	bloem.add_function(func1, 1);
	bloem.add_function(func0, 0);
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