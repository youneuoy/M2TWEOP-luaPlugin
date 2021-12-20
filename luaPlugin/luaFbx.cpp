///
//![Lua logo](../Lua.png)
//M2TWEOP structures and functions. There are not many examples and descriptions here. Also note that the examples do not include many of the checks that would be required when creating modifications.
//@module LuaPlugin
//@author youneuoy
//@license GPL-3.0
#include "luaP.h"
#include "plugData.h"


void luaP::initEopFbx()
{
	///M2TWEOPFBX table section
	//@section M2TWEOPFBXTable

	/***
	Basic M2TWEOPFBX table. Contains descriptions of m2tweop fbx feathures.
	addFbxModel addFbxModel
	deleteFbxModel deleteFbxModel

	@table M2TWEOPFBX
	*/



	tables.M2TWEOPFBXTable = luaState.create_table("M2TWEOPFBX");


	/***
	Load new fbx model
	@function M2TWEOPFBX.addFbxModel
	@tparam string modelPath path to .fbx file
	@tparam string texturePath path to .dds file
	@tparam int modelID id what be used for this model

	@usage
	M2TWEOPDU.addFbxModel("eopData/testmodel.fbx","eopData/testtexture.dds",1);
	*/
	tables.M2TWEOPFBXTable.set_function("addFbxModel", &eopFbxHelpers::addFbxModel);

	/***
	Delete fbx model
	@function M2TWEOPFBX.deleteFbxModel
	@tparam int modelID model id

	@usage
	--1 is id here
	M2TWEOPDU.addFbxModel("eopData/testmodel.fbx","eopData/testtexture.dds",1);
	M2TWEOPDU.deleteFbxModel(1);
	*/
	tables.M2TWEOPFBXTable.set_function("deleteFbxModel", &eopFbxHelpers::deleteFbxModel);


	/***
	Get fbx model
	@function M2TWEOPFBX.getFbxModel
	@tparam int modelID model id

	@usage
	--1 is id here
	M2TWEOPDU.addFbxModel("eopData/testmodel.fbx","eopData/testtexture.dds",1);
	local ourNewModel=M2TWEOPDU.getFbxModel(1);
	*/
	tables.M2TWEOPFBXTable.set_function("getFbxModel", &eopFbxHelpers::getFbxModel);
}
