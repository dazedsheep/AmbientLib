#ifndef _LOGGER_H_
#define _LOGGER_H_


namespace _log
{

class logger
{
private:

	std::string *buffer;

public:
	logger(void);
	~logger(void);

	
	void append(char a);
	void append(unsigned char a);
	void append(unsigned int a);
	void append(int a);
	void append(unsigned short a);
	void append(short a);
	void append(const char *a);
	void append(std::string& a);
	void append(unsigned __int64 a);
	void append(float a);
	void append(double a);
	std::string &lib_str();
	const char* c_str();

	size_t size();
};

static char endl='\n';

}

_log::logger& operator<<(_log::logger& out, char c);
_log::logger& operator<<(_log::logger& out, unsigned char c);
_log::logger& operator<<(_log::logger& out, unsigned int c);
_log::logger& operator<<(_log::logger& out, int c);
_log::logger& operator<<(_log::logger& out, unsigned short c);
_log::logger& operator<<(_log::logger& out, short c);
_log::logger& operator<<(_log::logger& out, const char *c);
_log::logger& operator<<(_log::logger& out, unsigned long c);
_log::logger& operator<<(_log::logger& out, std::string &c);
_log::logger& operator<<(_log::logger& out, unsigned __int64 c);
_log::logger& operator<<(_log::logger& out, float c);
_log::logger& operator<<(_log::logger& out, double c);

#endif
