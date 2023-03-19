#pragma once
#include <string>
#include "GoToken.h"
class GoLexer
{
private:
	std::string m_file;
	size_t m_at;
	char8_t m_cur;
	char8_t m_last;
	bool m_peeking;
	void SkipWhitespace();
	void Advance();
	char8_t Read();
public:
	explicit GoLexer(std::string const& GoFile);

	GoToken Next();
};

