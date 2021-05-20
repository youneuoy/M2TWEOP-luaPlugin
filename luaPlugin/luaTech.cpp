///
//![Lua logo](_static/Lua.png)
//M2TWEOP structures and functions. There are not many examples and descriptions here. Also note that the examples do not include many of the checks that would be required when creating modifications.
//@module Technical
//@author youneuoy
//@license GPL-3.0
#include "luaP.h"
#include "plugData.h"
#include "gameDataAllHelper.h"
#include "battleHandlerHelpers.h"
void luaP::initTech()
{
	///uniString table section
	//@section uniString

	/***
	Basic uniString table

	@tfield int Length used by game
	@tfield int MaximumLength used by game
	@tfield PWSTR Buffer utf-16 buffer, dont have good support in lua. Used by game
	@tfield convertToStr convertToStr make utf-8 version, you can use this in your stuff 
	@tfield createString setString set your utf-8 string to game, 

	@table uniString
	*/
	techTypes.uniString = luaState.new_usertype<UNICODE_STRING>("uniString");
}