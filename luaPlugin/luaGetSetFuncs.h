#pragma once
#define generalStruct_abilityID 1


#define generalCharactericticsStruct_shortName 1
#define generalCharactericticsStruct_fullName 2
#define generalCharactericticsStruct_label 3
#define generalCharactericticsStruct_modelName 4
#define generalCharactericticsStruct_portrait 5
#define generalCharactericticsStruct_portrait2 6
#define generalCharactericticsStruct_portrait_custom 7

#define EduEntryStruct_portrait_Type 1


#define anchillaryStruct_name 1
#define anchillaryStruct_imagePath 2
#include <string>
#include "realGameTypes.h"
namespace luaGetSetFuncs
{
	void setGameString(char* targetP, const char* newS);



#pragma region anchillary
	//anchillary
	template <char fieldIndex>
	std::string getStringProperty(const anchillary* anch)
	{
		char* retS = nullptr;
		if (fieldIndex == anchillaryStruct_name)
		{
			retS = anch->anchName;
		}
		else if (fieldIndex == anchillaryStruct_imagePath)
		{
			retS = anch->patchToAnchImage;
		}

		if (retS != nullptr)
		{
			return std::string(retS);
		}
		else
		{
			return std::string("");
		}
	}

	template <char fieldIndex>
	void setStringProperty(anchillary* anch, std::string newS)
	{
		char* arg = nullptr;
		if (fieldIndex == anchillaryStruct_name)
		{

			arg = reinterpret_cast<char*>(&anch->anchName);
		}
		else if (fieldIndex == anchillaryStruct_imagePath)
		{

			arg = reinterpret_cast<char*>(&anch->patchToAnchImage);
		}
		setGameString(arg, newS.c_str());
	}
#pragma endregion


#pragma region general


	//general
	template <char fieldIndex>
	std::string getStringProperty(const general* gen)
	{
		char* retS = nullptr;
		if (fieldIndex == generalStruct_abilityID)
		{
			retS = gen->ability;
		}

		if (retS != nullptr)
		{
			return std::string(retS);
		}
		else
		{
			return std::string("");
		}
	}

	template <char fieldIndex>
	void setStringProperty(general* gen, std::string newS)
	{
		char* arg = nullptr;
		if (fieldIndex == generalStruct_abilityID)
		{

			arg = reinterpret_cast<char*>(&gen->ability);
		}
		setGameString(arg, newS.c_str());
	}
#pragma endregion

#pragma region generalCharacterictics


	//generalCharacterictics
	template <char fieldIndex>
	std::string getStringProperty(const generalCharacterictics* genChar)
	{
		char* retS = nullptr;
		if (fieldIndex == generalCharactericticsStruct_shortName)
		{
			retS = genChar->shortName;
		}
		else if (fieldIndex == generalCharactericticsStruct_fullName)
		{
			retS = genChar->fullName;
		}
		else if (fieldIndex == generalCharactericticsStruct_label)
		{
			retS = genChar->label;
		}
		else if (fieldIndex == generalCharactericticsStruct_modelName)
		{
			retS = genChar->modelName;
		}
		else if (fieldIndex == generalCharactericticsStruct_portrait)
		{
			retS = genChar->portrait;
		}
		else if (fieldIndex == generalCharactericticsStruct_portrait2)
		{
			retS = genChar->portrait2;
		}
		else if (fieldIndex == generalCharactericticsStruct_portrait_custom)
		{
			retS = genChar->portrait2;
		}

		if (retS != nullptr)
		{
			return std::string(retS);
		}
		else
		{
			return std::string("");
		}
	}
	template <char fieldIndex>
	void setStringProperty(generalCharacterictics* genChar, std::string newS)
	{
		char* arg = nullptr;
		if (fieldIndex == generalCharactericticsStruct_shortName)
		{

			arg = reinterpret_cast<char*>(&genChar->shortName);
		}
		else if (fieldIndex == generalCharactericticsStruct_fullName)
		{

			arg = reinterpret_cast<char*>(&genChar->fullName);
		}
		else if (fieldIndex == generalCharactericticsStruct_label)
		{

			arg = reinterpret_cast<char*>(&genChar->label);
		}
		else if (fieldIndex == generalCharactericticsStruct_modelName)
		{

			arg = reinterpret_cast<char*>(&genChar->modelName);
		}
		else if (fieldIndex == generalCharactericticsStruct_portrait)
		{

			arg = reinterpret_cast<char*>(&genChar->portrait);
		}
		else if (fieldIndex == generalCharactericticsStruct_portrait2)
		{

			arg = reinterpret_cast<char*>(&genChar->portrait2);
		}
		else if (fieldIndex == generalCharactericticsStruct_portrait_custom)
		{

			arg = reinterpret_cast<char*>(&genChar->portrait2);
		}

		setGameString(arg, newS.c_str());
	}
#pragma endregion


#pragma region EduEntry


	//general
	template <char fieldIndex>
	std::string getStringProperty(const EduEntry* eduEn)
	{
		char* retS = nullptr;
		if (fieldIndex == EduEntryStruct_portrait_Type)
		{
			retS = eduEn->Type;
		}

		if (retS != nullptr)
		{
			return std::string(retS);
		}
		else
		{
			return std::string("");
		}
	}

	template <char fieldIndex>
	void setStringProperty(EduEntry* eduEn, std::string newS)
	{
		char* arg = nullptr;
		if (fieldIndex == EduEntryStruct_portrait_Type)
		{

			arg = reinterpret_cast<char*>(&eduEn->Type);
		}
		setGameString(arg, newS.c_str());
	}
#pragma endregion
};

