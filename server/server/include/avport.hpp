#pragma once

class AVFrame;
class AVPort
{
public:
	virtual void port_info();
	virtual bool put_frame(AVFrame* frame);
	virtual AVFrame* get_frame();
};