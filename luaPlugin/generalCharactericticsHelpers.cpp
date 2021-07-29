#include "generalCharactericticsHelpers.h"
#include "plugData.h"
namespace generalCharactericticsHelpers
{
	anchillary* getAnchillary(generalCharacterictics* character, int index)
	{
		return character->anchillaries[index]->dataAnch;

	}
	int addAnchillary(generalCharacterictics* character, std::string anchName)
	{
		anchillary* anch=(*(*plugData::data.funcs.findAnchillary))((char*)anchName.c_str());
		if (anch == nullptr)return 0;

		return (*(*plugData::data.funcs.addAnchillary))(character, anch);
	}
	void removeAnchillary(generalCharacterictics* character, anchillary* anch)
	{
		(*(*plugData::data.funcs.removeAnchillary))(character, anch);
	}
	int getAge(generalCharacterictics* character)
	{
		return (character->age >> 3) & 0x7f;
	}
	void setAge(generalCharacterictics* character, int age)
	{
		character->age = character->age ^ (age * 8 ^ character->age) & 0x3f8;
	}
	bool isAlive(generalCharacterictics* character)
	{
		return character->age&1;
	}
	void setAsHeir(generalCharacterictics* character, bool isJustSet)
	{
		(*(*plugData::data.funcs.setHeir))(character, isJustSet);
	}
}
