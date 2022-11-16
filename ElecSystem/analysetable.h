#ifndef ANALYSETABLE_H
#define ANALYSETABLE_H

#include <QString>


class AnalyseTable
{
public:
    AnalyseTable();
    void setArea(QString);
    void addData(double);
    void addScore(int);
    double getTotal();
    double getAverge();
    int getScore();
    QString getArea();
private:
    QString area;
    double total;
    int count;
    double average;
    int score;
};

#endif // ANALYSETABLE_H
