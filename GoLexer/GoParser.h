#pragma once
#include "GoLexer.h"
#include "GoProgram.h"

class GoParser
{
	std::string m_data;
public:
	GoParser(std::string const& Data);
	GoFile *Parse();


};

