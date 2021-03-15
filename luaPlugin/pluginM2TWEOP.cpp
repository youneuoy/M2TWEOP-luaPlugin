// pluginM2TWEOP.cpp : Определяет экспортируемые функции для DLL.
//

#include "pluginM2TWEOP.h"

#include "lua/sol.hpp"
#include <sol_ImGui.h>

int initPlugin(std::string* modPath)
{
    plugData::data.modFolder = *modPath;

    std::string plPath = plugData::data.modFolder;
    plPath = plPath + "\\HotSeatToolLib.dll";


    //onChangeTurnNum function
   /* std::string fName = "getYear";

    plugData::data.funcs.getYear.Load(&plPath, &fName);

    fName = "getBattleStacksListP";
    plugData::data.funcs.getBattleArmies.Load(&plPath, &fName);
    */
    std::string fName = "setCryptedString";
    plugData::data.funcs.setCryptedString.Load(&plPath, &fName);


    fName = "setModel";
    plugData::data.funcs.setModel.Load(&plPath, &fName);

    fName = "addModelToGame";
    plugData::data.funcs.addModelToGame.Load(&plPath, &fName);

    fName = "getFactionsCount";
    plugData::data.funcs.getFactionsCount.Load(&plPath, &fName);

    fName = "getFactionsList";
    plugData::data.funcs.getFactionsList.Load(&plPath, &fName);

    fName = "moveNormal";
    plugData::data.funcs.moveNormal.Load(&plPath, &fName);

    fName = "siegeSettlement";
    plugData::data.funcs.siegeSettlement.Load(&plPath, &fName);

    fName = "addAnchillary";
    plugData::data.funcs.addAnchillary.Load(&plPath, &fName);

    fName = "removeAnchillary";
    plugData::data.funcs.removeAnchillary.Load(&plPath, &fName);

    fName = "findAnchillary";
    plugData::data.funcs.findAnchillary.Load(&plPath, &fName);
    
    fName = "replaceTile";
    plugData::data.funcs.replaceTile.Load(&plPath, &fName);    

    fName = "moveStratCameraSlow";
    plugData::data.funcs.moveStratCameraSlow.Load(&plPath, &fName);

    fName = "moveStratCameraFast";
    plugData::data.funcs.moveStratCameraFast.Load(&plPath, &fName);

    fName = "zoomStratCamera";
    plugData::data.funcs.zoomStratCamera.Load(&plPath, &fName);

    fName = "teleportCharacter";
    plugData::data.funcs.teleportCharacter.Load(&plPath, &fName);

    fName = "createCharacter";
    plugData::data.funcs.createCharacter.Load(&plPath, &fName);

    fName = "setSoldiersCount";
    plugData::data.funcs.setSoldiersCount.Load(&plPath, &fName);

    fName = "setUnitParams";
    plugData::data.funcs.setUnitParams.Load(&plPath, &fName);

    fName = "killCharacter";
    plugData::data.funcs.killCharacter.Load(&plPath, &fName);


    fName = "createArmy";
    plugData::data.funcs.createArmy.Load(&plPath, &fName);


    fName = "createUnitN";
    plugData::data.funcs.createUnitN.Load(&plPath, &fName);

    fName = "createUnitIdx";
    plugData::data.funcs.createUnitIdx.Load(&plPath, &fName);

    fName = "addUnitToArmy";
    plugData::data.funcs.addUnitToArmy.Load(&plPath, &fName);

    fName = "setBodyguard";
    plugData::data.funcs.setBodyguard.Load(&plPath, &fName);
    
    fName = "attackCharacter";
    plugData::data.funcs.attackCharacter.Load(&plPath, &fName);




    initLua();
    return 1;
}

void initLua()
{
    std::string luaFile = plugData::data.modFolder + "\\youneuoy_Data\\plugins\\lua\\luaPluginScript.lua";

    sol::state* luaState = plugData::data.luaAll.init(luaFile, plugData::data.modFolder);
    if (luaState==nullptr)
    {
        MessageBoxA(NULL, "LUA loading error!", "Error!", NULL);
        exit(0);
    }
    sol_ImGui::Init(*luaState);
    MessageBoxA(NULL, "LUA HERE", "TEST", NULL);
}

