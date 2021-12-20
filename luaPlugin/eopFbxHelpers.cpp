#include "eopFbxHelpers.h"
#include "plugData.h"

void eopFbxHelpers::addFbxModel(const char* modelPath, const char* texturePath, int modelID)
{
	(*(*plugData::data.functsEopFbx.addFbxModel))(modelPath, texturePath, modelID);
}

void eopFbxHelpers::deleteFbxModel(int modelID)
{
	(*(*plugData::data.functsEopFbx.deleteFbxModel))(modelID);
}

void* eopFbxHelpers::getFbxModel(int modelID)
{
	return (*(*plugData::data.functsEopFbx.getFbxModel))(modelID);;
}
