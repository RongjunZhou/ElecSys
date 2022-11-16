#ifndef MEMINFO_H
#define MEMINFO_H

#include <QString>
#include <QList>

class MemInfo
{
public:
    MemInfo();
    MemInfo(QString,QString,QString,qreal,qreal,qreal);
    QString getarea();
    QString gethouse();
    QString getdate();
    qreal gethigh();
    qreal getlow();
    qreal getcharge();
    void setInfoForStaff(QString,QString,qreal);

private:
    QString area;
    QString house;
    QString date;
    qreal high;
    qreal low;
    qreal charge;

};

#endif // MEMINFO_H
