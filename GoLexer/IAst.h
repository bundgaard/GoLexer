#pragma once
#include <string>

class IAst
{
public:
	virtual std::string TokenLiteral() = 0;
	virtual std::string String() = 0;
};

