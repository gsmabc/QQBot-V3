#include <string>
#include "function.h"

std::string str::getFunName(std::string in)
{
	std::string out;
	for ( int i = 1; in.at(i) != ' '; i++ )
		out += in.at(i);
	return out;
}