#include "GoLexer.h"
#include <cstdio>
#include <vector>
static bool IsWhitespace(unsigned char Char)
{
	return Char == ' ';
}

void GoLexer::SkipWhitespace()
{
	unsigned char Current = Read();

	while(Current == ' ' || Current == '\r'||Current == '\n'||Current=='\t')
	{
		Current = Read();
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
	unsigned char Char = m_file[m_at++];
	return Char;
}

void GoLexer::Unread(unsigned char Char)
{
	m_peeking = true;
	m_last = Char;
}

unsigned char GoLexer::Peek()
{
	size_t Index = m_at;

	if (Index + 1 > m_file.length())
	{
		return 0;
	}
	unsigned char Next = m_file[m_at];
	return Next;
}

GoLexer::GoLexer(std::string const& GoFile) : m_file(GoFile), m_at(0), m_cur(0), m_peeking(false), m_last(0)
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
	
	if (Char == '"')
	{
		std::vector<unsigned char> Value;
		Char = Read();
		while (Char != '"')
		{
			Value.push_back(Char);
			Char = Read();
		}
		Char = Read(); // Eat the quote
		Unread(Char);
		return GoToken(GoToken::String, std::string{ Value.begin(), Value.end() });
	}
	else if (Char == '(')
	{
		return GoToken(GoToken::OpenParen, "(");
	}
	else if (Char == ')')
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
	else if (Char == '.')
	{
		return GoToken(GoToken::OperatorAndPunctuation, ".");
	}
	else if (Char == ':')
	{
		unsigned char Current = Char;
		unsigned char Next = Peek();
		if (Next == '=')
		{
			Char = Read();
			return GoToken(GoToken::OperatorAndPunctuation, ":=");
		}
		return GoToken(GoToken::OperatorAndPunctuation, ":");
	}
	else if (Char == '/')
	{
		unsigned char Current = Char;
		unsigned char Next = Peek();
		// Check for * 
		if (Next == '*')
		{
			Char = Read();
			// Read to the * and check if its ending with /
		}
		// Check for /
		if (Next == '/')
		{
			Char = Read();
			// Read to ENDOFLINE \r\n or \0
		}
		// Else
		return GoToken(GoToken::OperatorAndPunctuation, "/");


	}
	else if (Char == '*')
	{
		return GoToken(GoToken::OperatorAndPunctuation, "*");
	}
	else if (Char == '+')
	{
		return GoToken(GoToken::OperatorAndPunctuation, "+");
	}
	else if (Char == '-')
	{
		return GoToken(GoToken::OperatorAndPunctuation, "-");
	}
	else if (Char == ';')
	{
		return GoToken(GoToken::OperatorAndPunctuation, ";");
	}
	else if (Char >= '0' && Char <= '9')
	{
		std::vector<unsigned char> Value;
		while (Char >= '0' && Char <= '9')
		{
			Value.push_back(Char);
			Char = Read();
		}
		Unread(Char);
		return GoToken(GoToken::Number, std::string{ Value.begin(), Value.end() });
	}
	else
	{
		std::vector<unsigned char> Value;
		while ((Char >= 'a' && Char <= 'z') || (Char >= 'A' && Char <= 'Z'))
		{
			if (Char == ' ' || Char == '\0')
			{
				break;
			}
			Value.push_back(Char);

			Char = Read();
		}
		Unread(Char);
		return GoToken(GoToken::Identifier, std::string{ Value.begin(), Value.end() });
	}


	return GoToken(GoToken::Unknown, "unknown");
}
