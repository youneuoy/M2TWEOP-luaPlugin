#include "buildingStructHelpers.h"
namespace buildingStructHelpers
{
	std::string getType(building* build)
	{
		return build->bData->type;
	}
	std::string getName(building* build)
	{
		return (build->bData->drawInfo+ build->level)->name;
	}
}