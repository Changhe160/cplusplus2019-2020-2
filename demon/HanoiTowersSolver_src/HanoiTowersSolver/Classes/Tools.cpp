#include "StdAfx.h"
#include "Tools.h"

#include <sstream>

using std::string;
using std::ostringstream;

string Tools::IntToString(size_t number)
{
	ostringstream oss;
	
	oss<< number;
	
	return oss.str();
}