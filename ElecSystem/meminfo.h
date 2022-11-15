#ifndef MEMINFO_H
#define MEMINFO_H

#include <QString>
#include <QList>

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

    //查询数据数量
    int getMemCut();

    //增加用户
    bool addMem(MemInfo);

    //删除用户
    bool delMem(MemInfo);

    //清空用户表单
    void clearMemTable();

    //查询用户
    QList<MemInfo> getAllMem();

    //查询用户是否存在
    bool isExit(QString strMem);

    //添加单个用户
    void AddMem(MemInfo info);
    //删除单个用户
    void delMem(QString strMemName);

private:
    QString area;
    QString house;
    QString date;
    qreal high;
    qreal low;
    qreal charge;

};

#endif // MEMINFO_H
