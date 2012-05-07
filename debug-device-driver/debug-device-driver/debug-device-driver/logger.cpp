#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

using namespace _log;

logger::logger(void)
{
	buffer = new std::string();
}


logger::~logger(void)
{
}

std::string &logger::lib_str()
{
	return *buffer;
}

const char* logger::c_str()
{
	
	return buffer->c_str();
}

size_t logger::size()
{
	return buffer->size();
}

void logger::append(char a)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);;
	ss << a;
	buffer->append(ss.str());
}

void logger::append(unsigned char a)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);;
	ss << a;
	buffer->append(ss.str());
}

void logger::append(unsigned int a)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);;
	ss << a;
	buffer->append(ss.str());
}

void logger::append(int a)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);;
	ss << a;
	buffer->append(ss.str());
}


void logger::append(unsigned short a)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);;
	ss << a;
	buffer->append(ss.str());
}

void logger::append(short a)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);;
	ss << a;
	buffer->append(ss.str());
}

void logger::append(const char *a)
{
	buffer->append(a);
}

void logger::append(std::string &a)
{
	buffer->append(a);
}

void logger::append(unsigned __int64 a)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);;
	ss << a;
	buffer->append(ss.str());

}

void logger::append(float a)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);;
	ss << a;
	buffer->append(ss.str());
}

void logger::append(double a)
{
	std::stringstream ss(std::stringstream::in | std::stringstream::out);;
	ss << a;
	buffer->append(ss.str());
}

_log::logger& operator<<(_log::logger& out, char c)
{
	out.append(c);
	return out;
}
_log::logger& operator<<(_log::logger& out, unsigned char c)
{
	out.append(c);
	return out;
}
_log::logger& operator<<(_log::logger& out, unsigned int c)
{
	out.append(c);
	return out;
}
_log::logger& operator<<(_log::logger& out, int c)
{
	out.append(c);
	return out;
}
_log::logger& operator<<(_log::logger& out, unsigned short c)
{
	out.append(c);
	return out;
}
_log::logger& operator<<(_log::logger& out, short c)
{
	out.append(c);
	return out;

}

_log::logger& operator<<(_log::logger& out, unsigned long c)
{
	out.append((unsigned int)c);	// not nice i know ...
	return out;
}


_log::logger& operator<<(_log::logger& out, const char *c)
{
	out.append(c);
	return out;
}

_log::logger& operator<<(_log::logger& out, std::string &c)
{
	out.append(c);
	return out;
}

_log::logger& operator<<(_log::logger& out, unsigned __int64 c)
{
	out.append(c);
	return out;
}

_log::logger& operator<<(_log::logger& out, float c)
{
	out.append(c);
	return out;
}

_log::logger& operator<<(_log::logger& out, double c)
{
	out.append(c);
	return out;
}