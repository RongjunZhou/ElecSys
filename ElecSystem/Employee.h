#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QMainWindow>

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

private:
    Ui::Employee *ui;
};

#endif // EMPLOYEE_H
