#include "luaGetSetFuncs.h"
#include "plugData.h"
void luaGetSetFuncs::setGameString(char* targetP, const char* newS)
{
	(*(*plugData::data.funcs.setCryptedString))(targetP, newS);

}
