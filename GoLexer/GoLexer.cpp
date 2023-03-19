#include "GoLexer.h"
#include <cstdio>

void GoLexer::SkipWhitespace()
{
	char8_t Current = m_file[m_at];
	printf("Skipwhitespace %c\n", Current);
	for (;;)
	{
		if (Current == ' ')
		{
			Current = m_file[++m_at];
		}
		else {
			break;
		}
	}
	m_last = Current;
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
	char8_t Char = m_file[m_at++];
	printf("'%c'\n", Char);
	if (Char == ' ')
	{

	}
	else if (Char >= '0' || Char <= '9')
	{
		return GoToken(GoToken::Number, "aNumber");
	}
	else if (Char == '"')
	{
		return GoToken(GoToken::Identifier, "aString");
	}
	else
	{
		return GoToken(GoToken::Identifier, "anIdentifier");
	}


	return GoToken(GoToken::Unknown, "unknown");
}
