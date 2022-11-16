#include "analysetable.h"

AnalyseTable::AnalyseTable()
{
    this->count = 0;
    this->total = 0;
    this->score= 0;
}
void AnalyseTable::addData(double data)
{
    this->total+=data;
    count++;
    this->average=data/count;
}
void AnalyseTable::addScore(int score){
    this->score+=score;
}
double AnalyseTable::getTotal()
{
    return this->total;
}
double AnalyseTable::getAverge()
{
    return this->average;
}
int AnalyseTable::getScore()
{
    return this->score;
}
void AnalyseTable::setArea(QString area)
{
    this->area = area;
}
QString AnalyseTable::getArea()
{
    return this->area;
}
