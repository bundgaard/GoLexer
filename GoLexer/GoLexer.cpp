#include "GoLexer.h"
#include <cstdio>

void GoLexer::SkipWhitespace()
{

}

void GoLexer::Advance()
{
}

GoLexer::GoLexer(std::string const& GoFile) : m_file(GoFile), m_at(0), m_cur(0)
{
}

GoToken GoLexer::Next()
{
	SkipWhitespace();
	
	for (auto& Char : m_file)
	{
		printf("%c\n", Char);
	}
	return GoToken(GoToken::Unknown, "unknown");
}
