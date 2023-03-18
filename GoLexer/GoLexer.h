#pragma once
#include <string>
#include "GoToken.h"
class GoLexer
{
private:
	std::string m_file;
	size_t m_at;
	char8_t m_cur;

	void SkipWhitespace();
	void Advance();
public:
	explicit GoLexer(std::string const& GoFile);

	GoToken Next();
};

