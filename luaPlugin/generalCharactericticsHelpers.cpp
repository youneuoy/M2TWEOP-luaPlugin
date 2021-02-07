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
}
