#pragma once
#include <string>
#include "realGameTypes.h"
namespace technicalHelpers
{
	std::string unitUniStringToStr(unit*unit);
	void setUnitUniStr(unit* unit, const char* str);

	std::string uniStringToStr(UNICODE_STRING**& uniString);

}; 

