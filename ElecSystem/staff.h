#ifndef STAFF_H
#define STAFF_H

#include <QWidget>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class Staff;
}

class Staff : public QWidget
{
    Q_OBJECT

public:
    explicit Staff(QWidget *parent = nullptr);
    ~Staff();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_6_released();

    void on_pushButton_4_released();

    void on_pushButton_5_released();

    void on_pushButton_7_released();

    void on_pushButton_8_released();

private:
    Ui::Staff *ui;
    QSqlDatabase database;
    QSqlQuery *query;
};

#endif // STAFF_H
