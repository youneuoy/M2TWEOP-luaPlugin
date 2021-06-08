#include "technicalHelpers.h"

#include "plugData.h"


namespace technicalHelpers
{
	std::string unitUniStringToStr(unit* unit)
	{
		return uniStringToStr(unit->alias);
	}
	void setUnitUniStr(unit* unit, const char* str)
	{
		(*(*plugData::data.funcsTech.createUniString))(unit->alias, str);
	}
	std::string uniStringToStr(UNICODE_STRING**& uniString)
	{
		UNICODE_STRING* uniS = *uniString;
		wchar_t* wstr = (wchar_t*)&uniS->Buffer;

		std::string strTo;
		char* szTo = new char[uniS->Length + 1];
		szTo[uniS->Length] = '\0';
		WideCharToMultiByte(CP_ACP, 0, wstr, -1, szTo, (int)uniS->Length, NULL, NULL);

		strTo = szTo;
		delete[] szTo;

		return strTo;
	}

};

