#pragma once
#include "framework.h"
#include <d3d9.h>
#include <sstream>
class basicStructs
{
public:
	struct arm {
		//numbers of units
		UINT32 num;

		//army pointer
		stackStruct* army;


		//condition destroy_or_rout_enemy 
		UINT32 condDest;
		//condition capture settlement
		UINT32 condSetl;
		//defender or not
		UINT32 ifDef;
		//side in battle(0-3)
		UINT32 side;

		//deployment data offset
		DWORD deploy;

		//units
		std::vector<unit*>units;
	};

};


// functions loader
template <class T>
class ProcLoader
{
public:
	T			 m_pProc;
	std::string			m_strNameProcedure;

	//strings for compare
	char* stringAdr = nullptr;
	const char* strCmp;

	ProcLoader() {};

	BOOL Load(std::string* pczNameLibrary, std::string* pczNameProcedure, char* sCmp = nullptr)
	{
		m_strNameProcedure = *pczNameProcedure;
		m_pProc = NULL;
		strCmp = sCmp;
		HANDLE hModule;

		if (!(hModule = ::LoadLibraryA(pczNameLibrary->c_str())))
		{
			std::stringstream error;
			error << "Could not load plugin located at:\n" << pczNameProcedure->c_str() << "\n" << "Error Code: " << GetLastError();
			MessageBoxA(NULL, error.str().c_str(), "Error", NULL);
			return FALSE;
		}
		if (!(m_pProc = (T)::GetProcAddress((HMODULE)hModule, m_strNameProcedure.c_str())))
		{
			std::stringstream error2;
			error2 << "Can't load function: " << m_strNameProcedure.c_str();
			m_pProc = (T)emptyProc;
			MessageBoxA(NULL, error2.str().c_str(), "Attention", NULL);
			return FALSE;
		}
		return TRUE;
	};

	T operator *() const
	{
		return m_pProc;
	}

	static void emptyProc()
	{

	}
private:
	ProcLoader& operator = (ProcLoader&)
	{
		return *this;
	};
};

class battleFuncs
{
public:
	ProcLoader<int(__cdecl*)(DWORD)> getBattleCondCode;
	ProcLoader<void(__cdecl*)()> swUnBMapHighlight;
};
class technicalFuncs
{
public:
	ProcLoader<void(__cdecl*)(UNICODE_STRING**&, const char*)> createUniString;
};
class basicFuncs
{
public:
	ProcLoader<int(__cdecl*)(const char* counterName, bool&)> getScriptCounter;
	ProcLoader<void(__cdecl*)(const char*, int)> setScriptCounter;


	ProcLoader<bool(__cdecl*)(int*)> isTileFree;
	ProcLoader<gameDataAllStruct*(__cdecl*)()> getGameDataAll;


	ProcLoader<void(__cdecl*)(signed short, signed short)> setEDUUnitsSize;
	ProcLoader<void(__cdecl*)(generalCharacterictics*, bool)> setHeir;


	ProcLoader<void(__cdecl*)(unsigned char)> setAncLimit;
	ProcLoader<void(__cdecl*)(unsigned char)> setReligionsLimit;
	ProcLoader<void(__cdecl*)(unsigned char)> setMaxBgSize;
	ProcLoader<void(__cdecl*)()> unlockConsoleCommands;
	ProcLoader<void(__cdecl*)(int, int)> setConversionLvlFromCastle;
	ProcLoader<void(__cdecl*)(int, int)> setConversionLvlFromCity;


	//get current game year
	ProcLoader<UINT32(__cdecl*)()> getYear;
	ProcLoader<void(__cdecl*)(char*,const char*)> setCryptedString;
	ProcLoader<void(__cdecl*)(int,int,UINT32,UINT32)> setModel;
	ProcLoader<void(__cdecl*)(const char*,UINT32)> addModelToGame;
	ProcLoader<UINT32(__cdecl*)()> getFactionsCount;
	ProcLoader<factionStruct** (__cdecl*)()> getFactionsList;


	ProcLoader<void (__cdecl*)(general*, int, int)> moveNormal;
	ProcLoader<void (__cdecl*)(general*, settlementStruct*)> siegeSettlement;
	ProcLoader<void(__cdecl*)(general*, general*)> attackCharacter;


	ProcLoader<int (__cdecl*)(generalCharacterictics*, anchillary*)> addAnchillary;
	ProcLoader<void(__cdecl*)(generalCharacterictics*, anchillary*)> removeAnchillary;
	ProcLoader<anchillary*(__cdecl*)(char*)> findAnchillary;

	ProcLoader<void(__cdecl*)(const char*, UINT32, UINT32, const char*, const char*, const char*)> replaceTile;
	ProcLoader<void(__cdecl*)(int,int)> moveStratCameraSlow;
	ProcLoader<void(__cdecl*)(int,int)> moveStratCameraFast;
	ProcLoader<void(__cdecl*)(float)> zoomStratCamera;
	ProcLoader<void(__cdecl*)(general*, int, int)> teleportCharacter;

	//get list of armies in battle
	ProcLoader<std::vector<basicStructs::arm*>* (__cdecl*)()> getBattleArmies;


	ProcLoader< general*(__cdecl*)(const char*, factionStruct*, int, const char*, const char*, int, const char*, int, int)> createCharacter;

	ProcLoader<void(__cdecl*)(unit*)> killUnit;
	ProcLoader<void(__cdecl*)(general*)> killCharacter;

	ProcLoader<void(__cdecl*)(unit*,int)> setSoldiersCount;
	ProcLoader<void(__cdecl*)(unit*,int,int,int,int)> setUnitParams;

	ProcLoader<stackStruct*(__cdecl*)(general*)> createArmy;
	ProcLoader<unit*(__cdecl*)(const char*, int, int, int, int)> createUnitN;
	ProcLoader<unit*(__cdecl*)(int, int, int, int, int)> createUnitIdx;
	ProcLoader<unit*(__cdecl*)(int, int, int, int, int)> createUnitEDB;

	ProcLoader<int(__cdecl*)(stackStruct*,unit*)> addUnitToArmy;
	ProcLoader<void(__cdecl*)(general*,unit*)> setBodyguard;


	ProcLoader<void(__cdecl*)(settlementStruct*, const char*, bool)> destroyBuilding;
	ProcLoader<void(__cdecl*)(settlementStruct*, const char*)> createBuilding;




	//graphics
	ProcLoader<LPDIRECT3DTEXTURE9(__cdecl*)(const char*, int*, int*)> loadTexture;
	ProcLoader<void(__cdecl*)(LPDIRECT3DTEXTURE9)> unloadTexture;



};


class eopEduFuncs
{
public:
	//edu functions
	ProcLoader<EduEntry* (__cdecl*)(int, int)> addEopEduEntry;
	ProcLoader<EduEntry* (__cdecl*)(int)> getEopEduEntry;
	ProcLoader<int (__cdecl*)(int)> getDataEopEdu;


	ProcLoader<void (__cdecl*)(int, const char*)> setEntryUnitCardTga;
	ProcLoader<void (__cdecl*)(int, const char*)> setEntryInfoCardTga;
	ProcLoader<void (__cdecl*)(int, const char*)> setEntrySoldierModel;

	ProcLoader<void (__cdecl*)(int, const char*)> setEntryLocalizedName;
	ProcLoader<void (__cdecl*)(int, const char*)> setEntryLocalizedDescr;
	ProcLoader<void (__cdecl*)(int, const char*)> setEntryLocalizedShortDescr;
};