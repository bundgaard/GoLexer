#pragma once
#include <string>
#include "GoToken.h"
class GoLexer
{
private:
	std::string m_file;
	size_t m_at;
	unsigned char m_cur;
	unsigned char m_last;
	bool m_peeking;
	void SkipWhitespace();
	void Advance();
	unsigned char Read();
	unsigned char ReadChar();
	void Unread(unsigned char Char);
public:
	explicit GoLexer(std::string const& GoFile);

	GoToken Next();
};

