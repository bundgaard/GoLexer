#pragma once
#include <string>
namespace Tretton63
{

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

	inline std::string TokenToString(GoToken::GoType TokenType)
	{
		switch (TokenType)
		{
		case GoToken::String:
			return "String";

		case GoToken::Number:
			return "Number";

		case GoToken::Identifier:
			return "Identifier";

		case GoToken::OpenBracket:
		case GoToken::CloseBracket:
			return "Bracket";

		case GoToken::OpenParen:
		case GoToken::CloseParen:
			return "Parenthesis";

		case GoToken::OpenCurly:
		case GoToken::CloseCurly:
			return "Curly";

		case GoToken::OperatorAndPunctuation:
			return "Operators and Punctuation";

		default:
			return "TBA";
		}
	}

}