#include "GoToken.h"

GoToken::GoToken(GoType TokenType, std::string const& Value) : m_token(TokenType), m_value(Value)
{
}

GoToken::GoType GoToken::Token()
{
	return m_token;
}

std::string GoToken::Value() const
{
	return m_value;
}
