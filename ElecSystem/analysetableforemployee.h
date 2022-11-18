#ifndef ANALYSETABLEFOREMPLOYEE_H
#define ANALYSETABLEFOREMPLOYEE_H

#include <QString>

class AnalyseTableForEmployee
{
public:
    AnalyseTableForEmployee(QString area,double all_power,double all_fee,double averpower,double averfee);
    QString area;
    double all_power;
    double all_fee;
    double averpower;
    double averfee;
};

#endif // ANALYSETABLEFOREMPLOYEE_H
