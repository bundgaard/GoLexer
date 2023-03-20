#pragma once
#include "IAst.h"
class Statement :
	public IAst
{
public:
	virtual void statementNode() = 0;
};

