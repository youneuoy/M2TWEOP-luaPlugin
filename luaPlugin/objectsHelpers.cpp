#include "objectsHelpers.h"
#include "plugData.h"
void objectsHelpers::setModel(int x, int y, UINT32 modelId, UINT32 modelId2)
{
	(*(*plugData::data.funcs.setModel))(x, y, modelId, modelId2);
}
void objectsHelpers::addModelToGame(std::string path, UINT32 modelId)
{
	(*(*plugData::data.funcs.addModelToGame))(path.c_str(), modelId);
}


void objectsHelpers::replaceTile(std::string tileLabel, UINT32 x, UINT32 y, std::string fileName, std::string weather, std::string dayTime)
{
	(*(*plugData::data.funcs.replaceTile))(tileLabel.c_str(), x,y, fileName.c_str(), weather.c_str(), dayTime.c_str());
}
