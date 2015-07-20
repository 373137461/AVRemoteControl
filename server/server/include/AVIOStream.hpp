#pragma once

#include "precompile.hpp"

class AVIStream
{
public:
	virtual AVFrame* get_frame() = 0;
};

class AVOStream
{

};