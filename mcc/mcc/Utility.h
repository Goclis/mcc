#include <sstream>
#include <string>
using std::string;
using std::stringstream;

class Utility
{
public:
	static string string_concat_int(const string &head, int i)
	{
		stringstream sstm;
		sstm << head << i;
		return sstm.str();
	}
};

