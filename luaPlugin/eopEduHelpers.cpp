#include "eopEduHelpers.h"

#include "plugData.h"
EduEntry* eopEduHelpers::addEopEduEntry(int baseIndex, int newIndex)
{
    return (*(*plugData::data.funcsEopEdu.addEopEduEntry))(baseIndex, newIndex);;
}

EduEntry* eopEduHelpers::getEopEduEntry(int index)
{
    return (*(*plugData::data.funcsEopEdu.getEopEduEntry))(index);
}

int eopEduHelpers::getDataEopDu(int index)
{
    return (*(*plugData::data.funcsEopEdu.getDataEopEdu))(index);
}

void eopEduHelpers::setEntryUnitCardTga(int index, const char* newCard)
{
    (*(*plugData::data.funcsEopEdu.setEntryUnitCardTga))(index, newCard);

}

void eopEduHelpers::setEntryInfoCardTga(int index, const char* newCard)
{
    (*(*plugData::data.funcsEopEdu.setEntryInfoCardTga))(index, newCard);
}

void eopEduHelpers::setEntrySoldierModel(int index, const char* newModel)
{
    (*(*plugData::data.funcsEopEdu.setEntrySoldierModel))(index, newModel);
}

void eopEduHelpers::setEntryLocalizedName(int index, const char* newLocName)
{
    (*(*plugData::data.funcsEopEdu.setEntryLocalizedName))(index, newLocName);
}

void eopEduHelpers::setEntryLocalizedDescr(int index, const char* newLocDescr)
{
    (*(*plugData::data.funcsEopEdu.setEntryLocalizedDescr))(index, newLocDescr);
}

void eopEduHelpers::setEntryLocalizedShortDescr(int index, const char* newLocShortDescr)
{
    (*(*plugData::data.funcsEopEdu.setEntryLocalizedShortDescr))(index, newLocShortDescr);
}

unit* eopEduHelpers::createUnitByIndex(int index, int facNum, int exp, int arm, int weap)
{
    int unit=getDataEopDu(index);

    return (*(*plugData::data.funcs.createUnitEDB))(unit, facNum, exp, arm, weap);
}
