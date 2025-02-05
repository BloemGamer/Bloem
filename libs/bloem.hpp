#include <filesystem>

class bloem
{
private:
	std::filesystem::path filename;
	/* data */
public:
	void setup(char* filename);
	void run();


	bloem(/* args */);
	~bloem();
};


