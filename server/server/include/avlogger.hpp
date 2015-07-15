#pragma once

#include <iostream>
class AVLogger
{
public:
	static std::ostream& debug() { return std::clog; }
};
