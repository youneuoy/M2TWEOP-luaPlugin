#pragma once
#include "framework.h"
#include <d3d9.h>
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
	ProcLoader() {};

	BOOL Load(std::string* pczNameLibrary, std::string* pczNameProcedure)
	{
		m_strNameProcedure = pczNameProcedure->c_str();
		m_pProc = NULL;
		std::string message;
		HANDLE hModule;
		if (!(hModule = ::LoadLibraryA(pczNameLibrary->c_str())))
		{
			message = "Не могу загрузить ";
			message = message + *pczNameLibrary;

			::MessageBoxA(0, message.c_str(), "Ошибка", MB_OK | MB_ICONSTOP);
			return FALSE;
		}
		if (!(m_pProc = (T)::GetProcAddress((HMODULE)hModule, m_strNameProcedure.c_str())))
		{
			message = "Не найдена функция ";
			message = message + m_strNameProcedure;
			message = message + "в модуле";
			message = message + *pczNameLibrary;
			::MessageBoxA(0, message.c_str(), "Ошибка", MB_OK | MB_ICONSTOP);
			return FALSE;
		}
		return TRUE;
	};

	T proc;
	T operator *() const
	{
		return m_pProc;
	}

private:
	ProcLoader& operator = (ProcLoader&)
	{
		return *this;
	};
private:
	T			 m_pProc;
	std::string			m_strNameProcedure;
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
	ProcLoader<gameDataAllStruct*(__cdecl*)()> getGameDataAll;


	ProcLoader<void(__cdecl*)(unsigned char)> setAncLimit;
	ProcLoader<void(__cdecl*)(unsigned char)> setReligionsLimit;
	ProcLoader<void(__cdecl*)(unsigned char)> setMaxBgSize;
	ProcLoader<void(__cdecl*)()> unlockConsoleCommands;

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

	ProcLoader<int(__cdecl*)(stackStruct*,unit*)> addUnitToArmy;
	ProcLoader<void(__cdecl*)(general*,unit*)> setBodyguard;


	ProcLoader<void(__cdecl*)(settlementStruct*, const char*, bool)> destroyBuilding;
	ProcLoader<void(__cdecl*)(settlementStruct*, const char*)> createBuilding;




	//graphics
	ProcLoader<LPDIRECT3DTEXTURE9(__cdecl*)(const char*, int*, int*)> loadTexture;
	ProcLoader<void(__cdecl*)(LPDIRECT3DTEXTURE9)> unloadTexture;
};
