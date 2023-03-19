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
		Number,
		OperatorAndPunctuation
	};

	GoToken(GoType TokenType, std::string const& Value);

	GoType Token();
	std::string Value() const;
private:
	GoType m_token;
	
};

