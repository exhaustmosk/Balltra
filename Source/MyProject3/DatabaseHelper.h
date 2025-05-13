#pragma once

#include <string>

class DatabaseHelper
{
public:
	static bool RunSQLQuery(const std::string& Query, std::string& Result);
};
