#include "GoLexer.h"
#include <cstdio>
#include <vector>

void GoLexer::SkipWhitespace()
{
	unsigned char Current = Read();
	for (;;)
	{
		if (Current == ' ')
		{
			Current = Read();
		}
		else {
			break;
		}
	}
	Unread(Current);
}

void GoLexer::Advance()
{
}

unsigned char GoLexer::Read()
{
	if (m_peeking) {
		m_peeking = false;
		return m_last;
	}
	return ReadChar();
}

unsigned char GoLexer::ReadChar()
{
	if (m_at + 1 > m_file.length())
	{
		return 0; // return 0 for our end character
	}
	return m_file[m_at++];
}

void GoLexer::Unread(unsigned char Char)
{
	m_peeking = true;
	m_last = Char;
}

GoLexer::GoLexer(std::string const& GoFile) : m_file(GoFile), m_at(0), m_cur(0)
{
}

GoToken GoLexer::Next()
{
	SkipWhitespace();
	unsigned char Char = Read();
	if (Char == 0)
	{
		return GoToken(GoToken::Eof, "<EOF>");
	}

	if (Char == ' ')
	{
		SkipWhitespace();
	}
	else if (Char >= '0' && Char <= '9')
	{
		return GoToken(GoToken::Number, "aNumber");
	}
	else if (Char == '"')
	{
		std::vector<unsigned char> Value;
		Char = Read();
		while (Char != '"')
		{
			Value.push_back(Char);
		}
		return GoToken(GoToken::String, std::string{Value.begin(), Value.end()});
	}
	else if (Char == '(')
	{
		return GoToken(GoToken::OpenParen, "(");
	}
	else if (Char == '(')
	{
		return GoToken(GoToken::CloseParen, ")");
	}
	else if (Char == '[')
	{
		return GoToken(GoToken::OpenBracket, "[");
	}
	else if (Char == ']')
	{
		return GoToken(GoToken::CloseBracket, "]");
	}
	else if (Char == '{')
	{
		return GoToken(GoToken::OpenCurly, "{");
	}
	else if (Char == '}')
	{
		return GoToken(GoToken::CloseCurly, "}");
	}
	else
	{
		std::vector<unsigned char> Value;
		while (Char != ' ' && Char != 0)
		{
			SkipWhitespace();
			Value.push_back(Char);
			Char = Read();
		}
		return GoToken(GoToken::Identifier, std::string{Value.begin(), Value.end()});
	}


	return GoToken(GoToken::Unknown, "unknown");
}
