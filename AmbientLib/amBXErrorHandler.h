#ifndef ERROR_H
#define ERROR_H

#include <string>
#include "include/amBXSDK/amBX_Types.h"

class amBXErrorHandler
{
public:
	amBXErrorHandler();
	~amBXErrorHandler();
	static std::string getErrorMessage(amBX_RESULT errorNumber);
};

#endif
