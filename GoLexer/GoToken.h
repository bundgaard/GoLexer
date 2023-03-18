#pragma once
#include <string>

class GoToken
{
private:
	std::string m_value;

public:
	enum GoType {
		Unknown,
		Comment,
		Semicolon,
		Identifier,
		Keyword,
		OperatorAndPunctuation,
	};

	GoToken(GoType TokenType, std::string const& Value);

	GoType Token();
private:
	GoType m_token;
	std::string Value() const;
};

