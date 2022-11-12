#ifndef MEMINFO_H
#define MEMINFO_H

#include <QString>

class MemInfo
{
public:
    MemInfo(QString,QString,QString,qreal,qreal,qreal);
    QString getarea();
    QString gethouse();
    QString getdate();
    qreal gethigh();
    qreal getlow();
    qreal getcharge();

private:
    QString area;
    QString house;
    QString date;
    qreal high;
    qreal low;
    qreal charge;

};

#endif // MEMINFO_H
