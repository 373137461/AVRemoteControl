#pragma once

class AVLogger
{
public:
	static std::ostream& debug() { return std::clog; }
};
