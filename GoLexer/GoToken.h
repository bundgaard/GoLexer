#pragma once
#include <string>

class GoToken
{
private:
	std::string m_value;

public:
	enum GoType {
		Eof,
		Unknown,
		Comment,
		Semicolon,
		Identifier,
		Keyword,
		Number,
		String,
		OpenParen, CloseParen,
		OpenBracket, CloseBracket,
		OpenCurly, CloseCurly,
		OperatorAndPunctuation,
		CommentLine,
		CommentBlock
	};

	GoToken(GoType TokenType, std::string const& Value);

	GoType Token();
	std::string Value() const;
private:
	GoType m_token;
	
};

