#include "meminfo.h"

MemInfo::MemInfo(QString area,QString house,QString date,qreal high,qreal low,qreal charge)
{
    this->area = area;
    this->house = house;
    this->date = date;
    this->high = high;
    this->low = low;
    this->charge = charge;
}
MemInfo::MemInfo()
{

}
QString MemInfo::getarea(){
    return this->area;
}
QString MemInfo::gethouse(){
    return this->house;
}
QString MemInfo::getdate(){
    return this->date;
}
qreal MemInfo::gethigh(){
    return this->high;
}
qreal MemInfo::getlow(){
    return this->low;
}
qreal MemInfo::getcharge(){
    return this->charge;
}
void MemInfo::setInfoForStaff(QString area,QString house,qreal charge)
{
    this->area = area;
    this->house = house;
    this->charge = charge;
}
