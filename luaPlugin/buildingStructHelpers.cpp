#include "buildingStructHelpers.h"
namespace buildingStructHelpers
{
	std::string getType(building* build)
	{
		return build->bData->type;
	}
	std::string getName(building* build)
	{
		return (build->bData->drawInfo + build->level)->name;
	}
	std::string getQueueType(buildingInQueue* build)
	{
		return build->buildingData->type;
	}
	std::string getQueueName(buildingInQueue* build)
	{
		return (build->buildingData->drawInfo + build->currentLevel)->name;
	}
}