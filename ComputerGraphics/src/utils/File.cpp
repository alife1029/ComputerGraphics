#include "File.hpp"

#include <fstream>
#include <sstream>

std::string File::Read(const std::string& filePath)
{
	std::ifstream ifs(filePath);
	std::ostringstream oss;

	if (ifs.is_open())
	{
		oss << ifs.rdbuf();
	}

	ifs.close();
	return oss.str();
}
