#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class Employee;
}

class Employee : public QMainWindow
{
    Q_OBJECT

public:
    explicit Employee(QWidget *parent = nullptr);
    ~Employee();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_5_released();

    void on_pushButton_add_released();

    void on_pushButton_save_released();

    void on_pushButton_6_clicked();

private:
    Ui::Employee *ui;
    void *mainWindow;
    QString area;
    QString house;
    QString date;
    qreal high;
    qreal low;
    qreal charge;
    QSqlDatabase database;
    QSqlQuery *query;
};

#endif // EMPLOYEE_H
