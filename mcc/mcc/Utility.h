#ifndef UTILITY_H
#define UTILITY_H

#include <sstream>
#include <string>
using std::string;
using std::stringstream;

class Utility
{
public:
	/**
	 * @brief Concatenate string and integer.
	 */
	static string string_concat_int(const string &head, int i)
	{
		stringstream sstm;
		sstm << head << i;
		return sstm.str();
	}
};

#endif // UTILITY_H
