#ifndef ANALYSETABLE_H
#define ANALYSETABLE_H

#include <QString>


class AnalyseTable
{
public:
    AnalyseTable();
    void addData(double data);
    void setScore(int);
    void setUrgentNeed(bool);
    double getTotal();
    double getAverge();
    int getScore();
    bool getUrgentNeed();
private:
    double total;
    int count;
    double average;
    int score;
    bool urgentNeed;
};

#endif // ANALYSETABLE_H
