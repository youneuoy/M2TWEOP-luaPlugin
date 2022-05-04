﻿// pluginM2TWEOP.cpp : Определяет экспортируемые функции для DLL.
//

#include "pluginM2TWEOP.h"

#include "lua/sol.hpp"
#include <sol_ImGui.h>

int initPlugin(std::string* modPath)
{
    plugData::data.modFolder = *modPath;

    std::string plPath = plugData::data.modFolder;
    plPath = plPath + "\\M2TWEOPLibrary.dll";


    //onChangeTurnNum function
   /* std::string fName = "getYear";

    plugData::data.funcs.getYear.Load(&plPath, &fName);

    fName = "getBattleStacksListP";
    plugData::data.funcs.getBattleArmies.Load(&plPath, &fName);
    */
    std::string fName = "isTileFree";
    plugData::data.funcs.isTileFree.Load(&plPath, &fName);


    fName = "getTileRegionID";
    plugData::data.funcs.getTileRegionID.Load(&plPath, &fName);

    fName = "getRegionByID";
    plugData::data.funcs.getRegionByID.Load(&plPath, &fName);

    fName = "findFort";
    plugData::data.funcs.findFort.Load(&plPath, &fName);

    fName = "findSettlement";
    plugData::data.funcs.findSettlement.Load(&plPath, &fName);

    fName = "getRegionOwner";
    plugData::data.funcs.getRegionOwner.Load(&plPath, &fName);

    fName = "getGameDataAll";
    plugData::data.funcs.getGameDataAll.Load(&plPath, &fName);

    fName = "setEDUUnitsSize";
    plugData::data.funcs.setEDUUnitsSize.Load(&plPath, &fName);

    fName = "setHeir";
    plugData::data.funcs.setHeir.Load(&plPath, &fName);

    fName = "callGameConsoleCommand";
    plugData::data.funcs.callGameConsoleCommand.Load(&plPath, &fName);


    fName = "getScriptCounter";
    plugData::data.funcs.getScriptCounter.Load(&plPath, &fName);

    fName = "setScriptCounter";
    plugData::data.funcs.setScriptCounter.Load(&plPath, &fName);


    fName = "createUniString";
    plugData::data.funcsTech.createUniString.Load(&plPath, &fName);


   fName = "setCryptedString";
    plugData::data.funcs.setCryptedString.Load(&plPath, &fName);


    fName = "setReligionsLimit";
    plugData::data.funcs.setReligionsLimit.Load(&plPath, &fName);

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

    fName = "addTrait";
    plugData::data.funcs.addTrait.Load(&plPath, &fName);

    fName = "removeTrait";
    plugData::data.funcs.removeTrait.Load(&plPath, &fName);
    
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
    

    fName = "setUnitMovepoints";
    plugData::data.funcs.setUnitMovepoints.Load(&plPath, &fName);

    fName = "killUnit";
    plugData::data.funcs.killUnit.Load(&plPath, &fName);

    fName = "killCharacter";
    plugData::data.funcs.killCharacter.Load(&plPath, &fName);


    fName = "createArmy";
    plugData::data.funcs.createArmy.Load(&plPath, &fName);

    fName = "createArmyInSettlement";
    plugData::data.funcs.createArmyInSettlement.Load(&plPath, &fName);


    fName = "createUnitN";
    plugData::data.funcs.createUnitN.Load(&plPath, &fName);

    fName = "createUnitIdx";
    plugData::data.funcs.createUnitIdx.Load(&plPath, &fName);

    fName = "createUnitEDB";
    plugData::data.funcs.createUnitEDB.Load(&plPath, &fName);

    fName = "addUnitToArmy";
    plugData::data.funcs.addUnitToArmy.Load(&plPath, &fName);

    fName = "setBodyguard";
    plugData::data.funcs.setBodyguard.Load(&plPath, &fName);
    
    fName = "attackCharacter";
    plugData::data.funcs.attackCharacter.Load(&plPath, &fName);    


    fName = "loadTexture";
    plugData::data.funcs.loadTexture.Load(&plPath, &fName);

    fName = "unloadTexture";
    plugData::data.funcs.unloadTexture.Load(&plPath, &fName);


    fName = "setAncLimit";
    plugData::data.funcs.setAncLimit.Load(&plPath, &fName);


    fName = "unlockConsoleCommands";
    plugData::data.funcs.unlockConsoleCommands.Load(&plPath, &fName);

    fName = "setMaxBgSize";
    plugData::data.funcs.setMaxBgSize.Load(&plPath, &fName);

    fName = "setConversionLvlFromCastle";
    plugData::data.funcs.setConversionLvlFromCastle.Load(&plPath, &fName);

    fName = "setConversionLvlFromCity";
    plugData::data.funcs.setConversionLvlFromCity.Load(&plPath, &fName);


    fName = "destroyBuilding";
    plugData::data.funcs.destroyBuilding.Load(&plPath, &fName);

    fName = "createBuilding";
    plugData::data.funcs.createBuilding.Load(&plPath, &fName);

    fName = "setCharacterType";
    plugData::data.funcs.setCharacterType.Load(&plPath, &fName);
    



    //battle functions
    fName = "getBattleCondCode";
    plugData::data.funcsBattle.getBattleCondCode.Load(&plPath, &fName);   
    
    fName = "swUnBMapHighlight";
    plugData::data.funcsBattle.swUnBMapHighlight.Load(&plPath, &fName);


    //eop edu functions
    fName = "addEopEduEntry";
    plugData::data.funcsEopEdu.addEopEduEntry.Load(&plPath, &fName);  
     
    fName = "getEopEduEntry";
    plugData::data.funcsEopEdu.getEopEduEntry.Load(&plPath, &fName);    
    
    fName = "getDataEopEdu";
    plugData::data.funcsEopEdu.getDataEopEdu.Load(&plPath, &fName); 


    fName = "setEntryUnitCardTga";
    plugData::data.funcsEopEdu.setEntryUnitCardTga.Load(&plPath, &fName);

    fName = "setEntryInfoCardTga";
    plugData::data.funcsEopEdu.setEntryInfoCardTga.Load(&plPath, &fName);

    fName = "setEntrySoldierModel";
    plugData::data.funcsEopEdu.setEntrySoldierModel.Load(&plPath, &fName);

    fName = "setEntryLocalizedName";
    plugData::data.funcsEopEdu.setEntryLocalizedName.Load(&plPath, &fName);

    fName = "setEntryLocalizedDescr";
    plugData::data.funcsEopEdu.setEntryLocalizedDescr.Load(&plPath, &fName);

    fName = "setEntryLocalizedShortDescr";
    plugData::data.funcsEopEdu.setEntryLocalizedShortDescr.Load(&plPath, &fName);

    fName = "setBuildingChainLimit";
    plugData::data.funcs.setBuildingChainLimit.Load(&plPath, &fName);

    fName = "setGuildCooldown";
    plugData::data.funcs.setGuildCooldown.Load(&plPath, &fName);

    fName = "getGuild";
    plugData::data.funcs.getGuild.Load(&plPath, &fName);



    //fbx
    fName = "addFbxModel";
    plugData::data.functsEopFbx.addFbxModel.Load(&plPath, &fName);

    fName = "deleteFbxModel";
    plugData::data.functsEopFbx.deleteFbxModel.Load(&plPath, &fName);

    fName = "getFbxModel";
    plugData::data.functsEopFbx.getFbxModel.Load(&plPath, &fName);

    fName = "addFbxObject";
    plugData::data.functsEopFbx.addFbxObject.Load(&plPath, &fName);

    fName = "deleteFbxObject";
    plugData::data.functsEopFbx.deleteFbxObject.Load(&plPath, &fName);

    fName = "getFbxObject";
    plugData::data.functsEopFbx.getFbxObject.Load(&plPath, &fName);

    fName = "setFbxObjectCoords";
    plugData::data.functsEopFbx.setFbxObjectCoords.Load(&plPath, &fName);

    fName = "getFbxObjectCoords";
    plugData::data.functsEopFbx.getFbxObjectCoords.Load(&plPath, &fName);

    fName = "setFbxObjectSize";
    plugData::data.functsEopFbx.setFbxObjectSize.Load(&plPath, &fName);

    fName = "getFbxObjectSize";
    plugData::data.functsEopFbx.getFbxObjectSize.Load(&plPath, &fName);

    fName = "setFbxObjectDrawState";
    plugData::data.functsEopFbx.setFbxObjectDrawState.Load(&plPath, &fName);

    fName = "getFbxObjectDrawState";
    plugData::data.functsEopFbx.getFbxObjectDrawState.Load(&plPath, &fName);

    fName = "setFbxObjectAnimState";
    plugData::data.functsEopFbx.setFbxObjectAnimState.Load(&plPath, &fName);

    fName = "getFbxObjectAnimState";
    plugData::data.functsEopFbx.getFbxObjectAnimState.Load(&plPath, &fName);

    fName = "getFbxObjectDrawType";
    plugData::data.functsEopFbx.getFbxObjectDrawType.Load(&plPath, &fName);

    fName = "setFbxObjectDrawType";
    plugData::data.functsEopFbx.setFbxObjectDrawType.Load(&plPath, &fName);



    fName = "createEOPSound";
    plugData::data.functsEopSounds.createEOPSound.Load(&plPath, &fName);

    fName = "deleteEOPSound";
    plugData::data.functsEopSounds.deleteEOPSound.Load(&plPath, &fName);

    fName = "playEOPSound";
    plugData::data.functsEopSounds.playEOPSound.Load(&plPath, &fName);

    fName = "setEOPSoundOffset";
    plugData::data.functsEopSounds.setEOPSoundOffset.Load(&plPath, &fName);

    fName = "getEOPSoundOffset";
    plugData::data.functsEopSounds.getEOPSoundOffset.Load(&plPath, &fName);

    fName = "pauseEOPSound";
    plugData::data.functsEopSounds.pauseEOPSound.Load(&plPath, &fName);

    fName = "stopEOPSound";
    plugData::data.functsEopSounds.stopEOPSound.Load(&plPath, &fName);



    fName = "getUiElement";
    plugData::data.functsGameUI.getUiElement.Load(&plPath, &fName);

    fName = "useUiElement";
    plugData::data.functsGameUI.useUiElement.Load(&plPath, &fName);

    initLua();
    return 1;
}

void initLua()
{
    std::string luaFile = plugData::data.modFolder + "\\youneuoy_Data\\plugins\\lua\\luaPluginScript.lua";

    sol::state* luaState = plugData::data.luaAll.init(luaFile, plugData::data.modFolder);
    plugData::data.luaAll.initCampaign();
    plugData::data.luaAll.initP2();
    plugData::data.luaAll.initEopEdu();
    plugData::data.luaAll.initEopFbx();
    plugData::data.luaAll.initEopSounds();
    plugData::data.luaAll.initTech();
    plugData::data.luaAll.onPluginLoadF();
    if (luaState==nullptr)
    {
        MessageBoxA(NULL, "LUA loading error!", "Error!", NULL);
        exit(0);
    }
    sol_ImGui::Init(*luaState);
}

